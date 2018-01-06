#include "persistenceenginesql.h"

#include <iostream>

PersistenceEngineSQL::PersistenceEngineSQL()
    : PersistenceEngine()
{

}

std::string PersistenceEngineSQL::engineName() const
{
    return "SQL";
}

bool PersistenceEngineSQL::createNewLog(const std::string& logFileName, std::string& errMsg)
{
    errMsg = std::string(__FUNCTION__) + " Not implemented yet!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::openExistingLog (const std::string& logFileName, std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::deleteLog (const std::string& logFileName, std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::isOpen() const
{
    std::cout << std::string(__FUNCTION__) << ": Not yet implemented!\n";
    return false;
}

bool PersistenceEngineSQL::logExists(const std::string& logFileName) const
{
    std::cout << std::string(__FUNCTION__) << ": Not yet implemented!\n";
    return false;
}

bool PersistenceEngineSQL::writeVehicles(const std::vector<Vehicle>& v, std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::writeEvents(
        const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >&,
        std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::readVehicles(std::vector<Vehicle>& v, std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::readEvents(std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& e,
                                         std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

bool PersistenceEngineSQL::clearStorage (std::string& errMsg)
{
    errMsg.clear();

    errMsg = std::string(__FUNCTION__) + ": Not yet implemented!";
    std::cout << errMsg << "\n";
    return false;
}

void PersistenceEngineSQL::closeLog()
{
    std::cout << std::string(__FUNCTION__) << ": Not yet implemented!\n";
}
