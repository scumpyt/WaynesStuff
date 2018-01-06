#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>
#include <vector>

#include "persistenceenginefactoryut.h"
#include "persistenceenginefactory.h"
#include "vehicle.h"
#include "oilchangeevent.h"
#include "miscevent.h"
#include "scheduledmaintevent.h"
#include "tirerotationevent.h"

PersistenceEngineFactoryUT::PersistenceEngineFactoryUT()
{

}

void PersistenceEngineFactoryUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void PersistenceEngineFactoryUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void PersistenceEngineFactoryUT::init()
{
    // Runs before each test...
}

void PersistenceEngineFactoryUT::cleanup()
{
    // Runs at the end of each test...
}

void PersistenceEngineFactoryUT::testEngineName()
{
    {
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);
        QVERIFY(eng->engineName() == "CSV");
    }

    {
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::SQL);
        QVERIFY(eng->engineName() == "SQL");
    }

    {
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::NoEngine);
        QVERIFY(eng == nullptr);
    }
}
