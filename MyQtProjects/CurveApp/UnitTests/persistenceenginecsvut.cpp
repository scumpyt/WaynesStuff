#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>
#include <vector>
#include <sys/stat.h>       // For remove()

#include "persistenceenginecsvut.h"
#include "persistenceenginecsv.h"
#include "persistenceenginefactory.h"
#include "vehicle.h"
#include "oilchangeevent.h"
#include "miscevent.h"
#include "scheduledmaintevent.h"
#include "tirerotationevent.h"

PersistenceEngineCSVUT::PersistenceEngineCSVUT()
{

}

void PersistenceEngineCSVUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
    myLogFileName = "PersistenceEngineCSVUT";
}

void PersistenceEngineCSVUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...

    // Get rid of any left over log files permanently...
    remove(myLogFileName.c_str());
}

void PersistenceEngineCSVUT::init()
{
    // Runs before each test...
}

void PersistenceEngineCSVUT::cleanup()
{
    // Runs at the end of each test...
}

void PersistenceEngineCSVUT::testCreateNewLog()
{
    PersistenceEngineFactory pef;
    std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

    bool res;
    std::string errMsg;
    std::string fName(myLogFileName);
    QVERIFY(eng->deleteLog(fName, errMsg));

    QVERIFY(eng->logExists(fName) == false);

    res = eng->createNewLog(fName, errMsg);
    QVERIFY(res);
    QVERIFY(errMsg.empty());

    QVERIFY(eng->logExists(fName) == true);

    QVERIFY(eng->deleteLog(fName, errMsg) == true);
}

void PersistenceEngineCSVUT::testOpenExistingLog()
{
    PersistenceEngineFactory pef;
    std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

    bool res;
    std::string errMsg;
    std::string fName("KeepMe");
    QVERIFY(eng->deleteLog(fName, errMsg));

    // Create a file to play with...
    QVERIFY(eng->logExists(fName) == false);
    QVERIFY(eng->createNewLog(fName, errMsg));

    // Create vector of vehicles...
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
    Vehicle v2("Work Truck","Lexus","Blah","2004",25000);
    Vehicle v3("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
    Vehicle v4("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    std::vector<Vehicle> vect;
    vect.push_back(v1);
    vect.push_back(v2);
    vect.push_back(v3);
    vect.push_back(v4);

    // Write em out
    res = eng->writeVehicles(vect, errMsg);
    QVERIFY(res);

    // Close...
    eng->closeLog();
    QVERIFY(eng->logExists(fName) == true);
    QVERIFY(eng->isOpen() == false);

    // Now, reopen it...
    res = eng->openExistingLog(fName, errMsg);
    QVERIFY(res);
    QVERIFY(errMsg.empty());
    //QVERIFY(eng->deleteLog(fName, errMsg));
}

void PersistenceEngineCSVUT::testDeleteLog()
{
    PersistenceEngineFactory pef;
    std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

    std::string errMsg;
    std::string fName(myLogFileName);

    QVERIFY(eng->logExists(fName) == false);
    QVERIFY(eng->createNewLog(fName, errMsg));
    QVERIFY(eng->isOpen() == true);
    QVERIFY(eng->logExists(fName) == true);
    QVERIFY(eng->deleteLog(fName, errMsg));     // Will close the open file...
    QVERIFY(eng->isOpen() == false);
    QVERIFY(eng->logExists(fName) == false);
}

void PersistenceEngineCSVUT::testLogExists()
{
    PersistenceEngineFactory pef;
    std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

    // This test relies on the fact that we read, write, & look for files in 'current' dir,
    // which is where the exe is...
    QVERIFY(eng->logExists("UnitTests.exe"));
    QVERIFY(eng->logExists("Shouldn't find this one!") == false);
}

void PersistenceEngineCSVUT::testWriteVehicles()
{
    PersistenceEngineFactory pef;
    std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

    bool res;
    std::string errMsg;
    std::string fName(myLogFileName);
    QVERIFY(eng->deleteLog(fName, errMsg));

    res = eng->createNewLog(fName, errMsg);
    QVERIFY(res);
    QVERIFY(errMsg.empty());

    // Create vector of vehicles...
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
    Vehicle v2("Work Truck","Lexus","Blah","2004",25000);
    Vehicle v3("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
    Vehicle v4("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    std::vector<Vehicle> vect;
    vect.push_back(v1);
    vect.push_back(v2);
    vect.push_back(v3);
    vect.push_back(v4);

    res = eng->writeVehicles(vect, errMsg);
    QVERIFY(res);
    QVERIFY(errMsg.empty());

    QVERIFY(eng->deleteLog(fName, errMsg));
}

void PersistenceEngineCSVUT::testWriteEvents()
{
    PersistenceEngineFactory pef;
    std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

    bool res;
    std::string errMsg;
    std::string fName(myLogFileName);

    res = eng->createNewLog(fName, errMsg);
    QVERIFY(res);
    QVERIFY(errMsg.empty());

    // Create Vehicles to be used...
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
    Vehicle v2("Work Truck","Lexus","Blah","2004",25000);
    Vehicle v3("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
    Vehicle v4("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    // Now, manually create events & pair with Vehicles...
    std::unique_ptr<ServiceEventBase> uPtr;
    std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > > vect;

    uPtr.reset(new MiscEvent(1, "11/16/16", "Kramer Mazda", 134321,
                             "Replace front wipers.", 20));
    vect.push_back(std::make_pair(std::move(uPtr), v1));

    uPtr.reset(new OilChangeEvent(2, "04/23/17", "Bonavista Esso", 135123,
                                  "Regular Spring/Autumn stuff.", 75));
    vect.push_back(std::make_pair(std::move(uPtr), v2));

    uPtr.reset(new TireRotationEvent(3, "04/23/17", "Bonavista Esso", 135123,
                                     "Regular Spring/Autumn stuff.", 125));
    vect.push_back(std::make_pair(std::move(uPtr), v3));

    uPtr.reset(new ScheduledMaintEvent(4, "04/23/17", "Bonavista Esso", 135123,
                                       "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                       20000, 18));
    vect.push_back(std::make_pair(std::move(uPtr), v4));

    res = eng->writeEvents(vect, errMsg);
    QVERIFY(res);
    QVERIFY(errMsg.empty());

    QVERIFY(eng->deleteLog(fName, errMsg));
}

void PersistenceEngineCSVUT::testReadVehicles()
{
    bool res;
    std::string errMsg;
    std::string fName(myLogFileName);

    std::vector<Vehicle> vect;  // The originals...

    {   // Step 1 - Create a file w/ some Vehicles...
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

        res = eng->createNewLog(fName, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        // -------------------------
        // Create Vehicles to be used...
        Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
        Vehicle v2("Work Truck","Lexus","Blah","2004",25000);
        Vehicle v3("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
        Vehicle v4("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

        vect.push_back(v1);
        vect.push_back(v2);
        vect.push_back(v3);
        vect.push_back(v4);

        res = eng->writeVehicles(vect, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        eng->closeLog();
        QVERIFY(!eng->isOpen());
    }

    // Step 2 - Now, open and test the read...
    {
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

        res = eng->openExistingLog(fName, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        std::vector<Vehicle> rVect;
        res = eng->readVehicles(rVect, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        // Now compare what was read to the originals...
        QVERIFY(rVect.size() == vect.size());
        for (int i=0; i<rVect.size(); ++i)
        {
            QVERIFY(rVect[i] == vect[i]);
        }

        eng->closeLog();

        QVERIFY(eng->deleteLog(fName, errMsg));
    }
}

void PersistenceEngineCSVUT::testReadEvents()
{
    bool res;
    std::string errMsg;
    std::string fName(myLogFileName);

    std::vector<Vehicle> vect;  // The originals...

    {   // Step 1 - Create a file w/ some Events...
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

        res = eng->createNewLog(fName, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        // Create Vehicles to be used...
        Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
        Vehicle v2("Work Truck","Lexus","Blah","2004",25000);
        Vehicle v3("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
        Vehicle v4("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

        // Now, manually create events & pair with Vehicles...
        std::unique_ptr<ServiceEventBase> uPtr;
        std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > > vect;

        uPtr.reset(new MiscEvent(1, "11/16/16", "Kramer Mazda", 134321,
                                 "Replace front wipers.", 20));
        vect.push_back(std::make_pair(std::move(uPtr), v1));

        uPtr.reset(new OilChangeEvent(2, "04/23/17", "Bonavista Esso", 135123,
                                      "Regular Spring/Autumn stuff.", 75));
        vect.push_back(std::make_pair(std::move(uPtr), v2));

        uPtr.reset(new TireRotationEvent(3, "04/23/17", "Bonavista Esso", 135123,
                                         "Regular Spring/Autumn stuff.", 125));
        vect.push_back(std::make_pair(std::move(uPtr), v3));

        uPtr.reset(new ScheduledMaintEvent(4, "04/23/17", "Bonavista Esso", 135123,
                                           "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                           20000, 18));
        vect.push_back(std::make_pair(std::move(uPtr), v4));

        res = eng->writeEvents(vect, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        eng->closeLog();
        QVERIFY(!eng->isOpen());
    }

    // Step 2 - Now, open and test the read...
    {
        PersistenceEngineFactory pef;
        std::unique_ptr<PersistenceEngine> eng = pef.makePersistenceEngine(PersistenceEngineTypes::CSV);

        res = eng->openExistingLog(fName, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > > eVect;
        res = eng->readEvents(eVect, errMsg);
        QVERIFY(res);
        QVERIFY(errMsg.empty());

        QVERIFY(eVect.size() == 4);
        QVERIFY(eVect[0].first->getNotes() == "Replace front wipers.");
        QVERIFY(eVect[1].first->getNotes() == "Regular Spring/Autumn stuff.");
        QVERIFY(eVect[2].first->getNotes() == "Regular Spring/Autumn stuff.");
        QVERIFY(eVect[3].first->getNotes() == "Coolant flushed.");

        QVERIFY(eVect[0].second.getName() == "Wayne's Car");
        QVERIFY(eVect[1].second.getName() == "Work Truck");
        QVERIFY(eVect[2].second.getName() == "The Toy");
        QVERIFY(eVect[3].second.getName() == "Another Car");

        eng->closeLog();

        QVERIFY(eng->deleteLog(fName, errMsg));
    }
}
