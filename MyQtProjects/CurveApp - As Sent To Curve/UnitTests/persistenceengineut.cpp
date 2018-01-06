#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>
#include <sstream>

#include "persistenceengineut.h"
#include "persistenceengine.h"
#include "tirerotationevent.h"
#include "oilchangeevent.h"
#include "scheduledmaintevent.h"
#include "miscevent.h"

PersistenceEngineUT::PersistenceEngineUT()
{

}

void PersistenceEngineUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void PersistenceEngineUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void PersistenceEngineUT::init()
{
    // Runs before each test...
}

void PersistenceEngineUT::cleanup()
{
    // Runs at the end of each test...
}

void PersistenceEngineUT::testParseVehicles()
{
    // Create some vehicles...
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
    Vehicle v2("Work Truck","Lexus","Blah","2004",25000);
    Vehicle v3("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
    Vehicle v4("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    std::stringstream s1, s2, s3, s4;
    Vehicle v;

    // Output the string from each vehicle, parse the string back into a Vehicle
    // and then make sure it's the same as the original...
    s1 << v1;
    QVERIFY(PersistenceEngine::parseLineForVehicle(s1.str(),v));
    QVERIFY(v == v1);

    s2 << v2;
    QVERIFY(PersistenceEngine::parseLineForVehicle(s2.str(),v));
    QVERIFY(v == v2);

    s3 << v3;
    QVERIFY(PersistenceEngine::parseLineForVehicle(s3.str(),v));
    QVERIFY(v == v3);

    s4 << v4;
    QVERIFY(PersistenceEngine::parseLineForVehicle(s4.str(),v));
    QVERIFY(v == v4);

    QVERIFY(PersistenceEngine::parseLineForVehicle("This should fail!", v) == false);
    QVERIFY(v == Vehicle());

    QVERIFY(PersistenceEngine::parseLineForVehicle(std::string(), v) == false);
    QVERIFY(v == Vehicle());
}

void PersistenceEngineUT::testParseEvents()
{
    // Create some vehicles...
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
    Vehicle v2("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > inPair, outPair;
    std::unique_ptr<ServiceEventBase> uPtr;

    {   // TireRotationEvent...
        uPtr.reset(new TireRotationEvent(33, "04/23/17", "Bonavista Esso", 135123,
                                         "Regular Spring/Autumn stuff.", 125));
        inPair = std::make_pair(std::move(uPtr), v1);

        // Create the string from the event (pair)
        std::string str1 = PersistenceEngine::formatEventOutput(&(*inPair.first), inPair.second);

        // Now, create a new event from the string, and compare to orig...
        QVERIFY(PersistenceEngine::parseLineForEvent(str1, outPair));

        // Event comaprison...
        QVERIFY(*(dynamic_cast<TireRotationEvent*>(&(*outPair.first))) ==
                *(dynamic_cast<TireRotationEvent*>(&(*inPair.first ))));

        // Vehicle comparison...
        QVERIFY(outPair.second == inPair.second);   // Vehicle comparison...
    }

    {   // ScheduledMaintEvent...
        uPtr.reset(new ScheduledMaintEvent(33, "04/23/17", "Bonavista Esso", 135123,
                                          "Regular Spring/Autumn stuff.", 125,
                                           ScheduledMaintTypes::COOLANT_FLUSH,
                                           40000, 24));
        inPair = std::make_pair(std::move(uPtr), v2);

        // Create the string from the event (pair)
        std::string str1 = PersistenceEngine::formatEventOutput(&(*inPair.first), inPair.second);

        // Now, create a new event from the string, and compare to orig...
        QVERIFY(PersistenceEngine::parseLineForEvent(str1, outPair));

        // Event comaprison...
        QVERIFY(*(dynamic_cast<ScheduledMaintEvent*>(&(*outPair.first))) ==
                *(dynamic_cast<ScheduledMaintEvent*>(&(*inPair.first ))));

        // Vehicle comparison...
        QVERIFY(outPair.second == inPair.second);   // Vehicle comparison...
    }

    {   // OilChangeEvent...
        uPtr.reset(new OilChangeEvent(33, "04/23/17", "Bonavista Esso", 135123,
                                          "Regular Spring/Autumn stuff.", 125,
                                           40000, 24));
        inPair = std::make_pair(std::move(uPtr), v2);

        // Create the string from the event (pair)
        std::string str1 = PersistenceEngine::formatEventOutput(&(*inPair.first), inPair.second);

        // Now, create a new event from the string, and compare to orig...
        QVERIFY(PersistenceEngine::parseLineForEvent(str1, outPair));

        // Event comaprison...
        QVERIFY(*(dynamic_cast<OilChangeEvent*>(&(*outPair.first))) ==
                *(dynamic_cast<OilChangeEvent*>(&(*inPair.first ))));

        // Vehicle comparison...
        QVERIFY(outPair.second == inPair.second);   // Vehicle comparison...
    }

    {   // MiscEvent...
        uPtr.reset(new MiscEvent(33, "04/23/17", "Bonavista Esso", 135123,
                                          "Regular Spring/Autumn stuff.", 125));
        inPair = std::make_pair(std::move(uPtr), v1);

        // Create the string from the event (pair)
        std::string str1 = PersistenceEngine::formatEventOutput(&(*inPair.first), inPair.second);

        // Now, create a new event from the string, and compare to orig...
        QVERIFY(PersistenceEngine::parseLineForEvent(str1, outPair));

        // Event comaprison...
        QVERIFY(*(dynamic_cast<MiscEvent*>(&(*outPair.first))) ==
                *(dynamic_cast<MiscEvent*>(&(*inPair.first ))));

        // Vehicle comparison...
        QVERIFY(outPair.second == inPair.second);   // Vehicle comparison...
    }

    {
        QVERIFY(PersistenceEngine::parseLineForEvent("This should fail!", outPair) == false);
        QVERIFY(outPair.first  == nullptr);
        QVERIFY(outPair.second == Vehicle());
    }
}
