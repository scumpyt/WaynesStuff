#include "persistenceenginecsv.h"
#include "oilchangeevent.h"
#include "miscevent.h"
#include "scheduledmaintevent.h"
#include "tirerotationevent.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>

PersistenceEngineCSV::PersistenceEngineCSV()
    : PersistenceEngine()
{

}

std::string PersistenceEngineCSV::engineName() const
{
    return "CSV";
}

bool PersistenceEngineCSV::createNewLog(const std::string& logFileName, std::string& errMsg)
{
    errMsg.clear();
    setLogFileName("");

    // For ease of implementation, the following liberties where taken:
    // - Will simply overwrite any existing log file of the given name.
    // - Location of the files is location of exe.
    // Obviously, these would need to be addressed for a production version.

    if (logFileName.empty())
    {
        errMsg = std::string(__FUNCTION__) + ": Log file name invalid!";
        return false;
    }

    if (myFile.is_open())
    {
        // No need to save anything here, as it is about to be overwritten anyway...
        myFile.close();
    }

    myFile.clear();
    myFile.open(logFileName, std::ios::out|std::ios::trunc);
    if (!myFile.is_open())
    {
        errMsg = std::string(__FUNCTION__) + ": Log file could not be opened: " + strerror(errno);
        return false;
    }

    // Write a header line...
    myFile << "Maintenance Log file: " << logFileName << std::endl;

    setLogFileName(logFileName);    // Store log file name...

    return true;
}

bool PersistenceEngineCSV::openExistingLog (const std::string& logFileName, std::string& errMsg)
{
    errMsg.clear();
    setLogFileName("");

    if (logFileName.empty())
    {
        errMsg = std::string(__FUNCTION__) + ": Log file name invalid!";
        return false;
    }

    // Close any existing...
    if (myFile.is_open())
    {
        myFile.close();
    }

    myFile.clear();

    // Open for read...
    myFile.open(logFileName);
    if (!myFile.is_open())
    {
        errMsg = std::string(__FUNCTION__) + ": Log file could not be opened: " + strerror(errno);
        return false;
    }

    setLogFileName(logFileName);    // Store log file name...
    return true;
}

bool PersistenceEngineCSV::deleteLog (const std::string& logFileName, std::string& errMsg)
{
    errMsg.clear();

    if (logExists(logFileName))
    {
        if (logFileName == getLogFileName())
        {
            closeLog(); // In case it's open...
        }

        if (remove(logFileName.c_str()) != 0)
        {
            errMsg = std::string(__FUNCTION__) + ": Error deleting " + logFileName;
            return false;
        }
    }
    return true;
}

bool PersistenceEngineCSV::isOpen() const
{
    return myFile.is_open();
}

bool PersistenceEngineCSV::logExists(const std::string& logFileName) const
{
    // Not sure how cross-platform this might be...
    struct stat buf;
    if (stat(logFileName.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

bool PersistenceEngineCSV::writeVehicles(const std::vector<Vehicle>& v, std::string& errMsg)
{
    errMsg.clear();

    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // OK, write to log file...
    for (auto curVehicle : v)
    {
        myFile << curVehicle << std::endl;
    }

    return true;
}

bool PersistenceEngineCSV::writeEvents(const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& e,
                                       std::string& errMsg)
{
    errMsg.clear();

    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // OK, write to log file...
    for (auto itr=e.begin(); itr!=e.end(); ++itr)
    {
        myFile << PersistenceEngine::formatEventOutput(&(*itr->first), itr->second);
    }

    return true;
}

bool PersistenceEngineCSV::readVehicles(std::vector<Vehicle>& vVect, std::string& errMsg)
{
    errMsg.clear();
    vVect.clear();

    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Reposition file pointer to beginning...
    myFile.clear();
    myFile.seekg(0, std::ios::beg);

    // Read file, extract Vehicles, and add them to vector...
    std::string curLine;
    Vehicle v;
    while(std::getline(myFile, curLine))
    {
        if (PersistenceEngine::parseLineForVehicle(curLine, v))
        {
            vVect.push_back(v);
        }
    }

    return true;
}

bool PersistenceEngineCSV::readEvents(std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& eVect,
                                         std::string& errMsg)
{
    errMsg.clear();
    eVect.clear();

    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    // Reposition file pointer to beginning...
    myFile.clear();
    myFile.seekg(0, std::ios::beg);

    // Read file, extract Events, and add them to vector...
    std::string curLine;
    std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > ePair;

    while(std::getline(myFile, curLine))
    {
        if (PersistenceEngine::parseLineForEvent(curLine, ePair))
        {
            eVect.push_back(std::make_pair(std::move(ePair.first), ePair.second));
        }
    }

    return true;
}

bool PersistenceEngineCSV::clearStorage (std::string& errMsg)
{
    errMsg.clear();
    if (!checkForOpen(std::string(__FUNCTION__), errMsg)) return false;

    std::string saveFileName = getLogFileName();
    if (!saveFileName.empty())   // Sanity check...
    {
        // Quick & dirty way to clear contents of persitent storage.
        // Close the file, and reopen it for create..
        closeLog();
        if (!createNewLog(saveFileName, errMsg)) return false;
    }

    return true;
}

void PersistenceEngineCSV::closeLog()
{
    if (isOpen())
    {
        myFile.close();
        setLogFileName("");
    }
}
