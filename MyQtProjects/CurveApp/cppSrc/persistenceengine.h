#ifndef PERSISTENCEENGINE_H
#define PERSISTENCEENGINE_H

#include <string>
#include <vector>
#include <memory>

#include "vehicle.h"
#include "serviceeventbase.h"
#include "curve_global.h"

class CURVE_EXPORT PersistenceEngine
{
public:
    PersistenceEngine();

    // Disallow copying...
    PersistenceEngine(const PersistenceEngine&) = delete;
    PersistenceEngine& operator=(PersistenceEngine) = delete;

    ////////////////////////// Abstract Interface ///////////////////
    /// All Engines must implement the following:

    virtual std::string engineName      () const = 0;
    virtual bool        createNewLog    (const std::string& logFileName, std::string& errMsg) = 0;
    virtual bool        openExistingLog (const std::string& logFileName, std::string& errMsg) = 0;
    virtual bool        deleteLog       (const std::string& logFileName, std::string& errMsg) = 0;
    virtual bool        isOpen          () const = 0;
    virtual bool        logExists       (const std::string& logFileName) const = 0;

    virtual bool        writeVehicles   (const std::vector<Vehicle>& v, std::string& errMsg) = 0;
    virtual bool        writeEvents     (const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& e,
                                         std::string& errMsg) = 0;
    virtual bool        readVehicles    (std::vector<Vehicle>& v, std::string& errMsg) = 0;
    virtual bool        readEvents      (std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& e,
                                         std::string& errMsg) = 0;

    virtual bool        clearStorage    (std::string& errMsg) = 0;

    virtual void        closeLog() = 0;

    ////////////////////////// End of Abstract Interface ///////////////

    // Local methods...
    virtual std::string getLogFileName() const;
    virtual bool        checkForOpen(const std::string& funcName, std::string& errMsg) const;

    // Static method to ensure the formatting of event/vehicle pair is formatted in one place only...
    // (It is done in a couple of places)
    static std::string  formatEventOutput(const ServiceEventBase* event, const Vehicle& vehicle);

    // Static methods to parse text for Events/Vehicles...
    static bool         parseLineForVehicle(const std::string& inLine, Vehicle& outVehicle);
    static bool         parseLineForEvent  (const std::string& inLine,
                                            std::pair< std::unique_ptr<ServiceEventBase>, Vehicle >& outEvent);

protected:
    // Internal use only...
    virtual void        setLogFileName(const std::string& logFileName);

private:
    std::string         myLogFileName;
};

#endif // PERSISTENCEENGINE_H
