#ifndef PERSISTENCEENGINESQL_H
#define PERSISTENCEENGINESQL_H

#include "persistenceengine.h"

class PersistenceEngineSQL : public PersistenceEngine
{
public:
    PersistenceEngineSQL();


    virtual std::string engineName      () const;
    virtual bool        createNewLog    (const std::string& logFileName, std::string& errMsg);
    virtual bool        openExistingLog (const std::string& logFileName, std::string& errMsg);
    virtual bool        deleteLog       (const std::string& logFileName, std::string& errMsg);
    virtual bool        isOpen          () const;
    virtual bool        logExists       (const std::string& logFileName) const;

    virtual bool        writeVehicles   (const std::vector<Vehicle>& v, std::string& errMsg);
    virtual bool        writeEvents     (const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >&,
                                         std::string& errMsg);
    virtual bool        readVehicles    (std::vector<Vehicle>& v, std::string& errMsg);
    virtual bool        readEvents      (std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& e,
                                         std::string& errMsg);

    virtual bool        clearStorage    (std::string& errMsg);

    virtual void        closeLog();
};

#endif // PERSISTENCEENGINESQL_H
