#include "persistenceenginefactory.h"
#include "persistenceenginecsv.h"
#include "persistenceenginesql.h"
//#include "persistenceenginerest.h"

PersistenceEngineFactory::PersistenceEngineFactory()
{

}

std::unique_ptr<PersistenceEngine> PersistenceEngineFactory::makePersistenceEngine
                                  (PersistenceEngineTypes::PersistenceEngineType pType)
{
    std::unique_ptr<PersistenceEngine> engPtr;
    if (pType == PersistenceEngineTypes::CSV)
    {
        // create the CSV-based engine...
        engPtr.reset(new PersistenceEngineCSV());
    }
    else if (pType == PersistenceEngineTypes::SQL)
    {
        // create the SQL-base engine...
        engPtr.reset(new PersistenceEngineSQL());
    }
//    else if (pType == PersistenceEngineTypes::REST)
//    {
//        // create the REST-based engine...
//        engPtr.reset(new PersistenceEngineREST());
//    }

    return engPtr;
}
