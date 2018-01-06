#ifndef PERSISTENCEENGINEFACTORY_H
#define PERSISTENCEENGINEFACTORY_H

#include <memory>

#include "persistenceenginetypes.h"
#include "persistenceengine.h"
#include "curve_global.h"

class CURVE_EXPORT PersistenceEngineFactory
{
public:
    PersistenceEngineFactory();

    std::unique_ptr<PersistenceEngine>   makePersistenceEngine(PersistenceEngineTypes::PersistenceEngineType pType);
};

#endif // PERSISTENCEENGINEFACTORY_H
