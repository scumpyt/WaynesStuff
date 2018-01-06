#ifndef MAINTENANCELOG_H
#define MAINTENANCELOG_H

//////////////////////////////////////////////////////////////////////////////
/// Maintenance Log:
///
/// A library for tracking Automobile Maintenance events. You can keep
/// track several Vehicles, of various types (GAS, DIESEL, ELECTRIC), and
/// Events that occur on those Vehicles.
///
/// Several Event types are available, such as oil changes, tire rotations,
/// etc., but not all Events are compatible with all Vehicle types. E.g.,
/// an ELECTRIC car won't need an oil change.
///
/// You can only work on one Log at a time, and the basic flow is to either
/// create a new log, or open an existing one (which loads all existing into
/// memory. Then, you do all manipulations in-memory, such as add, remove,
/// or update both Vehicles and/or Events, and, when happy, you then save what
/// you have to persistent storage. If your not happy with what you have done,
/// you can simply close, and abandon all your changes.
///
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "curve_global.h"
#include "vehicle.h"
#include "serviceeventbase.h"
#include "oilchangeevent.h"
#include "tirerotationevent.h"
#include "scheduledmaintevent.h"
#include "miscevent.h"

#include "persistenceengine.h"

class CURVE_EXPORT MaintenanceLog
{
public:
    MaintenanceLog();
   ~MaintenanceLog();

    // Disallow copying...
    MaintenanceLog(const MaintenanceLog&) = delete;
    MaintenanceLog& operator=(MaintenanceLog) = delete;

    // --------------------------
    // Log file persistence funcs.

    //////////////////////////////////////////////////////////////////////////////
    /// \brief createNewLog         Create a new, empty log.
    /// \param fileName             Name of file to create. E.g. "TheLog.txt"
    ///                             Can't be blank.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Will silently clear any loaded log file info. If it hasn't been 'saved',
    /// it will be lost.
    ///
    /// \see logExists(), save()
    //////////////////////////////////////////////////////////////////////////////
    bool                            createNewLog(const std::string& fileName,
                                                 std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief openExistingLog      Open a Log previously saved to persistent
    ///                             storage.
    /// \param fileName             Name of file to open. Can't be blank.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Will fail if there is a file currently open. Call close() first.
    //////////////////////////////////////////////////////////////////////////////
    bool                            openExistingLog(const std::string& fileName,
                                                    std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief deleteLog            Permanently remove file from persistent
    ///                             storage.
    /// \param fileName             Name of file to remove. Can't be blank.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Does not have to be the currently open Log.
    ///
    /// If the currently open file matches the given fileName, it will be closed
    /// first. No save is bothered with, of course, as it's being removed anyway.
    //////////////////////////////////////////////////////////////////////////////
    bool                            deleteLog(const std::string& fileName,
                                              std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief isOpen               Is there a log file currently open.
    /// \return                     true if yes, false, if no.
    //////////////////////////////////////////////////////////////////////////////
    bool                            isOpen() const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief close                Close any currently open log file.
    ///
    /// No automatic 'save' done. This allows you to abandon current work.
    //////////////////////////////////////////////////////////////////////////////
    void                            close();

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getLogFileName       Retrieve the currently open log file name.
    /// \return                     The filename if a file is open, a blank
    ///                             string, if not.
    //////////////////////////////////////////////////////////////////////////////
    std::string                     getLogFileName() const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief save                 Will save the current(in memory)state
    ///                             (Vehicles/Events) to persistent storage.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Note that this does a 'replace' of any existing contents of perm. storage
    //////////////////////////////////////////////////////////////////////////////
    bool                            save(std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief clear                Removes all Vehicles and Events.
    //////////////////////////////////////////////////////////////////////////////
    void                            clear();

    //////////////////////////////////////////////////////////////////////////////
    /// \brief logExists            Does a log of this name exist?
    /// \param fileName             Filename to look for.
    /// \return                     true if yes, false if no.
    //////////////////////////////////////////////////////////////////////////////
    bool                            logExists(const std::string& fileName) const;

    // --------------------------
    // Vehicle API...
    // (the first 4 are the classic Create, Read, Update, Delete (CRUD) funcs  )

    //////////////////////////////////////////////////////////////////////////////
    /// \brief addVehicle           Add a new Vehicle.
    /// \param v                    Vehicle object to add.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// The Vehicle given must be completely defined (see Vehicle::isComplete()),
    /// and it's name must be unique amoung known Vehicles.
    //////////////////////////////////////////////////////////////////////////////
    bool                            addVehicle(const Vehicle& v,
                                               std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getVehicle           Get a copy of an existing Vehicle.
    /// \param vehicleName          Vehicle name to search for.
    /// \param outCopy              Returned Vehicle obj. (copy)
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// If a Vehicle of that name does not exist, or any problems encountered, the
    /// returned Vehicle object will be a default constructed version.
    //////////////////////////////////////////////////////////////////////////////
    bool                            getVehicle(const std::string& vehicleName,
                                               Vehicle& outCopy,
                                               std::string& errMsg) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief updateVehicle        Update an existing Vehicle.
    /// \param updatedVehicle       Vehicle object with updated values.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// We search for the Vehicle to update by name, thus, you can't 'update'
    /// the name field itself.
    //////////////////////////////////////////////////////////////////////////////
    bool                            updateVehicle(const Vehicle& updatedVehicle,
                                                  std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief removeVehicle        Remove a Vehicle from the Log.
    /// \param vehicleName          Vehicle name to search for.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// If this Vehicle is being used in any current Events, the remove will fail.
    /// \see                        isVehicleUsed()
    //////////////////////////////////////////////////////////////////////////////
    bool                            removeVehicle(const std::string& vehicleName,
                                                  std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief hasVehicle           Does a Vehicle of this name exist?
    /// \param vehicleName          Vehicle name to search for.
    /// \return                     true for yes, false for no.
    //////////////////////////////////////////////////////////////////////////////
    bool                            hasVehicle(const std::string& vehicleName) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief isVehicleUsed        Is the given Vehicle being used in any Events?
    /// \param vehicleName          Vehicle name to search for.
    /// \return                     true for yes, false for no.
    //////////////////////////////////////////////////////////////////////////////
    bool                            isVehicleUsed(const std::string& vehicleName) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getVehicles          Get a read-only copy of all Vehicles.
    /// \return                     A const reference to the vector of Vehicles.
    //////////////////////////////////////////////////////////////////////////////
    const std::vector<Vehicle>&     getVehicles() const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief listAllVehicles      Convenience func. to list all Vehicles to the
    ///                             given ostream.
    /// \param outStream            Will output to any derivation of ostream. E.g.
    ///                             std::cout for console, std::stringstream to
    ///                             write to a std::string.
    //////////////////////////////////////////////////////////////////////////////
    void                            listAllVehicles(std::ostream& outStream) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getNVehicles         How many Vehicles do I have?
    /// \return                     The current number of (in-memory) Vehicles.
    //////////////////////////////////////////////////////////////////////////////
    size_t                          getNVehicles() const;

    // --------------------------
    // Event API...

    //////////////////////////////////////////////////////////////////////////////
    /// \brief addEvent             Add a new Event to Log.
    /// \param e                    Event to add
    ///                             - Must be non-null
    ///                             - Must be a unique Id
    /// \param v                    Vehicle to associate with this Event.
    ///                             - Must be 'Complete'
    ///                             - Must be 'Known'
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Not all Event types and Vehicle Types are compatible. E.g., can't do an
    /// OilChange on an ELECTRIC car.
    //////////////////////////////////////////////////////////////////////////////
    bool                            addEvent(std::unique_ptr<ServiceEventBase> e,
                                             const Vehicle& v, std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getEvent             Get a copy of an Event by Id.
    /// \param eventIdToSearchFor   Id to search for.
    /// \param outCopy              Copy of the Event.
    ///                             Returns nullptr, if not found, or failure.
    /// \param outVehAtThisEvent    Copy of the Vehicle associated with this Event.
    ///                             Defaulted constructed Vehicle, if not found,
    ///                             or failure.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    //////////////////////////////////////////////////////////////////////////////
    bool                            getEvent(size_t eventIdToSearchFor,
                                             std::unique_ptr<ServiceEventBase>& outCopy,
                                             Vehicle& outVehAtThisEvent,
                                             std::string& errMsg) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief updateEvent          Update an existing Event.
    /// \param updatedEvent         The Event, with changes applied.
    /// \param updatedVehForEvent   The Vehicle associated with this Event.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Uses the Id to match Events, thus the Id field itself cannot be updated.
    //////////////////////////////////////////////////////////////////////////////
    bool                            updateEvent(std::unique_ptr<ServiceEventBase> updatedEvent,
                                                const Vehicle& updatedVehForEvent,
                                                std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief removeEvent          Remove an Event.
    /// \param eventIdToRemove      Id of the Event you wish to remove.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    //////////////////////////////////////////////////////////////////////////////
    bool                            removeEvent(size_t eventIdToRemove,
                                                std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief removeAllEvents      Remove all Events associated with the given
    ///                             Vehicle.
    /// \param forThisVehicle       Vehicle to look for in Events.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    ///
    /// Convenience function calls RemoveAllEvents(byName);
    //////////////////////////////////////////////////////////////////////////////
    bool                            removeAllEvents(const Vehicle& forThisVehicle,
                                                    std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief removeAllEvents      Remove all Events associated with the given
    ///                             Vehicle.
    /// \param vehicleName          Vehicle name to look for in Events.
    /// \param errMsg               Returned error message, if unsuccessful.
    /// \return                     true for success, false for failure.
    //////////////////////////////////////////////////////////////////////////////
    bool                            removeAllEvents(const std::string& vehicleName,
                                                    std::string& errMsg);

    //////////////////////////////////////////////////////////////////////////////
    /// \brief hasEvent             Does an Event of the given Id exist?
    /// \param eventIdToSearchFor   Id to search for.
    /// \return                     true for yes, false for no.
    //////////////////////////////////////////////////////////////////////////////
    bool                            hasEvent(size_t eventIdToSearchFor) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getEvents            Get a read-only copy of the Events.
    /// \return                     const reference to the vector Events
    //////////////////////////////////////////////////////////////////////////////
    const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >&
                                    getEvents() const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief listAllEvents        Convenience func. to list ALL Events.
    /// \param outStream            Will output to any derivation of ostream. E.g.
    ///                             std::cout for console, std::stringstream to
    ///                             write to a std::string.
    //////////////////////////////////////////////////////////////////////////////
    void                            listAllEvents(std::ostream& outStream) const;

    //////////////////////////////////////////////////////////////////////////////
    /// \brief getNLogEvents        How many Events do I have?
    /// \return                     The number of Events currently loaded.
    //////////////////////////////////////////////////////////////////////////////
    size_t                          getNLogEvents() const;

protected:

    // Internal helper funcs...
    bool                            checkForOpen(const std::string& func, std::string& errMsg) const;
    bool                            read(std::string& errMsg);

private:
    std::vector<Vehicle>                                                    myVehicles;
    std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >  myLogEvents;
    std::unique_ptr<PersistenceEngine>                                      myEngine;
};

#endif // MAINTENANCELOG_H
