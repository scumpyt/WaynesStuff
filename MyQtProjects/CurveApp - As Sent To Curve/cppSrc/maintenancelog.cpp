#include "maintenancelog.h"

#include <algorithm>
#include <sstream>

#include "persistenceenginefactory.h"
#include "persistenceenginecsv.h"
#include "persistenceenginesql.h"

#define MAX_NAME_LENGTH 60

MaintenanceLog::MaintenanceLog()
{
    // Create a CSV engine for our usage here...
    PersistenceEngineFactory pef;
    myEngine = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);
}

MaintenanceLog::~MaintenanceLog()
{
    close();
}

bool MaintenanceLog::createNewLog(const std::string& fileName, std::string& errMsg)
{
    return (myEngine->createNewLog(fileName, errMsg));
}

bool MaintenanceLog::openExistingLog(const std::string& fileName, std::string& errMsg)
{
    // Check if something open already...
    if (isOpen())
    {
        errMsg = std::string(__FUNCTION__) + ": Log already open!";
        return false;
    }

    // Open and read log...
    if (!myEngine->openExistingLog(fileName, errMsg)) return false;
    return read(errMsg);

}

bool MaintenanceLog::deleteLog(const std::string& fileName, std::string& errMsg)
{
    return (myEngine->deleteLog(fileName, errMsg));
}

bool MaintenanceLog::isOpen() const
{
    return (myEngine->isOpen());
}

void MaintenanceLog::close()
{
    // NOTE - not doing 'save' automatically here, to allow abandoning current work...
    myEngine->closeLog();
    clear();
}

std::string MaintenanceLog::getLogFileName() const
{
    return myEngine->getLogFileName();
}

bool MaintenanceLog::save(std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Clear any existing contents of the persistent storage...
    if (!myEngine->clearStorage(errMsg)) return false;

    // Now, do the writes...
    if (!myEngine->writeVehicles(getVehicles(), errMsg)) return false;
    if (!myEngine->writeEvents  (getEvents(),   errMsg)) return false;

    return true;
}

void MaintenanceLog::clear()
{
    myVehicles.clear();
    myLogEvents.clear();
}

bool MaintenanceLog::read(std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Do the reads...

    // ---
    // First, the Vehicles...
    std::vector<Vehicle> vVect;
    if (!myEngine->readVehicles(vVect, errMsg)) return false;

    // Add the returned Vehicles...
    for (auto v : vVect)
    {
        // But only if it doesn't exist already...
        if (!hasVehicle(v.getName()))
        {
            if (!addVehicle(v, errMsg))
                return false;
        }
    }

    // ---
    // Then, the Events...
    std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > > eVect;
    if (!myEngine->readEvents(eVect, errMsg)) return false;

    // Add the returned Events...
    for (auto itr=eVect.begin(); itr!=eVect.end(); ++itr)
    {
        // But only if it doesn't exist already...
        if (!hasEvent(itr->first->getId()))
        {
            if (!addEvent(std::move(itr->first), itr->second, errMsg))
                return false;
        }
    }

    return true;
}

bool MaintenanceLog::logExists(const std::string& fileName) const
{
    return myEngine->logExists(fileName);
}

///////////////////////////////////////////////
// -------------  Vehicle funcs  --------------
///////////////////////////////////////////////
bool MaintenanceLog::addVehicle(const Vehicle& v, std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Only add fully complete Vehicles...
    if (!v.isComplete())
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle is incomplete. Not added.";
        return false;
    }

    // Vehicle's must be unique base on names...
    auto itr = std::find_if(myVehicles.begin(), myVehicles.end(),
                            [v](Vehicle curVehicle) {return curVehicle.getName() == v.getName(); });

    if (itr != myVehicles.end())
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle '" + v.getName() + "' already exists.";
        return false;
    }

    // Add it!
    myVehicles.push_back(v);
    return true;
}

bool MaintenanceLog::getVehicle(const std::string& vehicleName, Vehicle& vOut, std::string& errMsg) const
{
    vOut = Vehicle();

    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    auto itr = std::find_if(myVehicles.begin(), myVehicles.end(),
                            [vehicleName](Vehicle curVehicle) {return curVehicle.getName() == vehicleName; });

    if (itr == myVehicles.end())
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle '" + vehicleName + "' not found.";
        return false;
    }

    vOut = *itr;
    return true;
}

bool MaintenanceLog::updateVehicle(const Vehicle& updatedVehicle, std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    auto itr = std::find_if(myVehicles.begin(), myVehicles.end(),
                            [updatedVehicle](Vehicle curVehicle) {return curVehicle.getName() == updatedVehicle.getName(); });

    if (itr == myVehicles.end())
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle '" + updatedVehicle.getName() + "' not found.";
        return false;
    }

    *itr = updatedVehicle;  // Replace...
    return true;
}

bool  MaintenanceLog::removeVehicle(const std::string& vehicleName, std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    if (isVehicleUsed(vehicleName))
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle '" + vehicleName + "' is being used in Events. Not removed.";
        return false;
    }

    auto itr = std::find_if(myVehicles.begin(), myVehicles.end(),
                            [vehicleName](Vehicle curVehicle) {return curVehicle.getName() == vehicleName; });

    if (itr == myVehicles.end())
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle '" + vehicleName + "' not found.";
        return false;
    }

    myVehicles.erase(itr);

    return true;
}

bool MaintenanceLog::hasVehicle(const std::string& vehicleName) const
{
    auto itr = std::find_if(myVehicles.begin(), myVehicles.end(),
                            [vehicleName](Vehicle curVehicle) {return curVehicle.getName() == vehicleName; });
    return (!(itr == myVehicles.end()));
}

bool MaintenanceLog::isVehicleUsed(const std::string& vehicleName) const
{
    // Search for match...
    for (auto itr=myLogEvents.begin(); itr!=myLogEvents.end(); ++itr)
    {
        if (itr->second.getName() == vehicleName)
        {
            return true;
        }
    }

    return false;
}

const std::vector<Vehicle>& MaintenanceLog::getVehicles() const
{
    return myVehicles;
}

void MaintenanceLog::listAllVehicles(std::ostream& outStream) const
{
    for(auto v : myVehicles)
    {
        outStream << v << std::endl;
    }
}

size_t MaintenanceLog::getNVehicles() const
{
    return myVehicles.size();
}

///////////////////////////////////////////////
// ------------- Log Event funcs --------------
///////////////////////////////////////////////
bool MaintenanceLog::addEvent(std::unique_ptr<ServiceEventBase> e, const Vehicle& v, std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Event must be non-null...
    if (!e)
    {
        errMsg = std::string(__FUNCTION__) + ": Event invalid (null). Not added.";
        return false;
    }

    // Event must be unique (ID)...
    if (hasEvent(e->getId()))
    {
        errMsg = std::string(__FUNCTION__) + ": Event '" + std::to_string(e->getId()) + "' already exists.";
        return false;
    }

    // Vehicle must be complete, and exist as one of our known Vehicles...
    if (!v.isComplete())
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle is incomplete. Not added.";
        return false;
    }

    // Vehicle must have been loaded previously.
    // NOTE - (Optionally, we could add any unknown vehicles automatically - Ask Product Owner)
    if (!hasVehicle(v.getName()))
    {
        errMsg = std::string(__FUNCTION__) + ": Vehicle '" + v.getName() + "' is unknown. Not added.";
        return false;
    }

    // Not all events valid for all Vehicle types...
    if (v.getVehicleType() == VehicleTypes::ELECTRIC && e->getName() == "Oil Change")
    {
        errMsg = std::string(__FUNCTION__) + ": Oil Change not allowed for Electric vehicles. Not added.";
        return false;
    }

    // Move it in!
    myLogEvents.push_back(std::make_pair(std::move(e), v));
    return true;
}

bool MaintenanceLog::getEvent(size_t eventIdToSearchFor,
                              std::unique_ptr<ServiceEventBase>& outCopy,
                              Vehicle& outVehicleAtThisEvent,
                              std::string& errMsg) const
{
    // clear...
    outCopy.reset(nullptr);
    outVehicleAtThisEvent = Vehicle();

    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Search for match...
    auto itrMatch = myLogEvents.end();
    for (auto itr=myLogEvents.begin(); itr!=myLogEvents.end(); ++itr)
    {
        if (itr->first->getId() == eventIdToSearchFor)
        {
            itrMatch = itr;
        }
    }

    if (itrMatch == myLogEvents.end())
    {
        errMsg = std::string(__FUNCTION__) + ": Event '" + std::to_string(eventIdToSearchFor) + "' doesn't exist.";
        return false;
    }

    // OK, a match was found...
    // Now, manually construct a COPY of that item pointed-to by the unique pointer.
    std::string derivedClassName = typeid(*itrMatch->first).name();
    if (derivedClassName == "class OilChangeEvent")
    {
        outCopy.reset(new OilChangeEvent(dynamic_cast<const OilChangeEvent&>(*(itrMatch->first))));
    }
    else if (derivedClassName == "class TireRotationEvent")
    {
        outCopy.reset(new TireRotationEvent(dynamic_cast<const TireRotationEvent&>(*(itrMatch->first))));
    }
    else if (derivedClassName == "class ScheduledMaintEvent")
    {
        outCopy.reset(new ScheduledMaintEvent(dynamic_cast<const ScheduledMaintEvent&>(*(itrMatch->first))));
    }
    else if (derivedClassName == "class MiscEvent")
    {
        outCopy.reset(new MiscEvent(dynamic_cast<const MiscEvent&>(*(itrMatch->first))));
    }
    else
    {
        // Should never happen, unless a new type is added, and this 'if' not updated for it...
        // A possible maintenance red flag, however, providing access through a collection of base class
        // pointers, there is probably no way around it. Benefits outweigh the potential issues.
        errMsg = std::string(__FUNCTION__) + ": EventType not handled.";
        return false;
    }

    // Now copy Vehicle...
    outVehicleAtThisEvent = itrMatch->second;

    return true;
}

bool MaintenanceLog::updateEvent(std::unique_ptr<ServiceEventBase> updatedEvent,
                                 const Vehicle& updatedVehicleForEvent,
                                 std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // updatedEvent can't be null...
    if (!updatedEvent)
    {
        errMsg = std::string(__FUNCTION__) + ": UpdatedEvent invalid (null). Not updated.";
        return false;
    }

    // Vehicle needs to be complete, and exist in log...
    if (!updatedVehicleForEvent.isComplete())
    {
        errMsg = std::string(__FUNCTION__) + ": updatedVehicleForEvent incomplete. Not updated.";
        return false;
    }
    if (!hasVehicle(updatedVehicleForEvent.getName()))
    {
         errMsg = std::string(__FUNCTION__) + ": Vehicle '" + updatedVehicleForEvent.getName()
                                            + "' is unknown. Not updated.";
        return false;
    }

    // OK, search for match...
    // Search for match...
    auto itrMatch = myLogEvents.end();
    for (auto itr=myLogEvents.begin(); itr!=myLogEvents.end(); ++itr)
    {
        if (itr->first->getId() == updatedEvent->getId())
        {
            itrMatch = itr;
        }
    }

    if (itrMatch == myLogEvents.end())
    {
        errMsg = std::string(__FUNCTION__) + ": Event '" + std::to_string(updatedEvent->getId()) + "' doesn't exist.";
        return false;
    }

    // Match found. Swap in given Event and Vehicle...
    itrMatch->first  = std::move(updatedEvent);
    itrMatch->second = updatedVehicleForEvent;

    return true;
}

bool MaintenanceLog::removeEvent(size_t eventIdToRemove, std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Search for event with given id...
    for (auto itr=myLogEvents.begin(); itr!=myLogEvents.end(); ++itr)
    {
        if (itr->first->getId() == eventIdToRemove)
        {
            // Found. Get rid of it...
            myLogEvents.erase(itr);
            return true;
        }
    }

    errMsg = std::string(__FUNCTION__) + ": Event '" + std::to_string(eventIdToRemove) + "' doesn't exist.";
    return false;
}

bool MaintenanceLog::removeAllEvents(const Vehicle& forThisVehicle, std::string& errMsg)
{
    return removeAllEvents(forThisVehicle.getName(), errMsg);
}

bool MaintenanceLog::removeAllEvents(const std::string& vehicleName, std::string& errMsg)
{
    // A log file must have been opened first...
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Erase/remove idiom...
    myLogEvents.erase(std::remove_if(myLogEvents.begin(),
                                     myLogEvents.end(),
                                     [&](const std::pair< std::unique_ptr<ServiceEventBase>, Vehicle >& curPair)-> bool
                                        { return curPair.second.getName() == vehicleName; }),
                                     myLogEvents.end());

    return true;
}

bool MaintenanceLog::hasEvent(size_t eventIdToSearchFor) const
{
    for (auto itr=myLogEvents.begin(); itr!=myLogEvents.end(); ++itr)
    {
        if (itr->first->getId() == eventIdToSearchFor)
        {
            return true;
        }
    }

    return false;
}

const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& MaintenanceLog::getEvents() const
{
    return myLogEvents;
}

void MaintenanceLog::listAllEvents(std::ostream& outStream) const
{
    for (auto itr=myLogEvents.begin(); itr!=myLogEvents.end(); ++itr)
    {
        outStream << PersistenceEngine::formatEventOutput(&(*itr->first), itr->second);
    }
}

size_t MaintenanceLog::getNLogEvents() const
{
    return myLogEvents.size();
}

bool MaintenanceLog::checkForOpen(const std::string& func, std::string& errMsg) const
{
    errMsg.clear();
    if (!isOpen())
    {
        errMsg = func + ": No file open yet.";
        return false;
    }
    return true;
}
