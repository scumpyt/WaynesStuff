#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>
#include <sstream>
#include <sys/stat.h>       // For remove()

#include "maintenancelogut.h"
#include "maintenancelog.h"

MaintenanceLogUT::MaintenanceLogUT()
{

}

void MaintenanceLogUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
    myLogFileName = "MaintenanceLogUT";
}

void MaintenanceLogUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...

    // Get rid of any log file permanently...
    remove(myLogFileName.c_str());
}

void MaintenanceLogUT::init()
{
    // Runs before each test...

    // Create fresh copies at start of each test...
    v1 = Vehicle("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::GAS);
    v2 = Vehicle("Work Truck","Lexus","Blah","2004",25000);
    v3 = Vehicle("The Toy", "Tesla","Model 3", "2017", 123, VehicleTypes::ELECTRIC);
    v4 = Vehicle("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);
}

void MaintenanceLogUT::cleanup()
{
    // Runs at the end of each test...

    // Clear at the end of each test...
    v1 = Vehicle();
    v2 = Vehicle();
    v3 = Vehicle();
    v4 = Vehicle();
}

void MaintenanceLogUT::testCtor()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));
}

/////////////////////////////
// ----- File I/O tests -----
void MaintenanceLogUT::testCreateNewLog()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;
    bool res = ml.createNewLog(myLogFileName, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());

    QVERIFY(ml.isOpen());
    QVERIFY(ml.getLogFileName() == myLogFileName);
    QVERIFY(ml.getNVehicles() == 0);
    QVERIFY(ml.getNLogEvents() == 0);
    QVERIFY(checkIfClosed(ml) == false);
}

void MaintenanceLogUT::testOpenExistingLog()
{
    std::string errMsg;
    std::string expectedResults;

    {   // First, create a fresh log to play with...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        QVERIFY(ml.getNVehicles() == 4);
        addEventsToLog(ml, v1, v2);
        QVERIFY(ml.getNLogEvents() == 5);

        QVERIFY(ml.save(errMsg));   // Save to disk...
        ml.close();
        QVERIFY(checkIfClosed(ml));
    }

    {   // Now open it...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));
        QVERIFY(ml.getNVehicles() == 0);
        QVERIFY(ml.getNLogEvents() == 0);

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }

    {   // Now open it a second time...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }

    {   // This time, open it once and then try to open again without closing...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);

        QVERIFY(!ml.openExistingLog("EvenToSomeDifferentName", errMsg));
        QVERIFY(errMsg.empty() == false);

        expectedResults = "MaintenanceLog::openExistingLog: Log already open!";
        QVERIFY(errMsg == expectedResults);

        QVERIFY(ml.getNVehicles() == 4);    // State not changed at all
        QVERIFY(ml.getNLogEvents() == 5);
        QVERIFY(ml.getLogFileName() == myLogFileName);

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }

    {   // Try to open non-existent file...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        QVERIFY(!ml.openExistingLog("Shouldn't find this one!", errMsg));
        QVERIFY(errMsg.empty() == false);
        QVERIFY(checkIfClosed(ml));         // Should be still closed...
    }
}

void MaintenanceLogUT::testDeleteLog()
{
    std::string errMsg;
    std::string expectedResults;

    {   // First, create a fresh log to play with...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        QVERIFY(ml.getNVehicles() == 4);
        addEventsToLog(ml, v1, v2);
        QVERIFY(ml.getNLogEvents() == 5);

        QVERIFY(ml.save(errMsg));
        ml.close();
        QVERIFY(checkIfClosed(ml));

        // Now delete it...
        QVERIFY(ml.logExists(myLogFileName));
        QVERIFY(ml.deleteLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.logExists(myLogFileName) == false);
    }

    {   // Non-existent file...
        MaintenanceLog ml;

        // Non-existent file just ignored...
        QVERIFY(ml.logExists("Shouldn't find this one!") == false);
        QVERIFY(ml.deleteLog("Shouldn't find this one!", errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.logExists("Shouldn't find this one!") == false);
    }

    {
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        QVERIFY(ml.getNVehicles() == 4);
        addEventsToLog(ml, v1, v2);
        QVERIFY(ml.getNLogEvents() == 5);

        // Save & close NOT done...

        // Deleting an open file will close & remove no problem
        QVERIFY(ml.logExists(myLogFileName));
        QVERIFY(ml.deleteLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.logExists(myLogFileName) == false);
    }
}

void MaintenanceLogUT::testClose()
{
    std::string errMsg;

    {   // First, create a fresh log to play with...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        addEventsToLog(ml, v1, v2);

        QVERIFY(ml.isOpen() == true);
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);
        QVERIFY(ml.getLogFileName().empty() == false);

        // Now close & verify...
        QVERIFY(checkIfClosed(ml) == false);
        ml.close();
        QVERIFY(checkIfClosed(ml) == true);

        // Check state explicitely...
        QVERIFY(ml.isOpen() == false);
        QVERIFY(ml.getNVehicles() == 0);
        QVERIFY(ml.getNLogEvents() == 0);
        QVERIFY(ml.getLogFileName().empty() == true);

        QVERIFY(ml.getVehicles().size() == 0);
        QVERIFY(ml.getEvents().size() == 0);

        // Calling close a second time should do nothing...
        ml.close();
        QVERIFY(checkIfClosed(ml) == true);
    }

    {
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Calling close on unopened log should do nothing...
        ml.close();
        QVERIFY(checkIfClosed(ml));
    }
}

void MaintenanceLogUT::testSave()
{
    std::string errMsg;
    //std::string expectedResults;

    {   // First, create a fresh log to play with...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        addEventsToLog(ml, v1, v2);

        // Now save to disk, and close...
        QVERIFY(ml.save(errMsg));
        QVERIFY(errMsg.empty());
        ml.close();
    }

    {   // Now open it...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));
        QVERIFY(ml.getNVehicles() == 0);
        QVERIFY(ml.getNLogEvents() == 0);

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);

        // Now verify it contains all we expect...

        // Vehicles...
        QVERIFY(ml.hasVehicle(v1.getName()));
        QVERIFY(ml.hasVehicle(v2.getName()));
        QVERIFY(ml.hasVehicle(v3.getName()));
        QVERIFY(ml.hasVehicle(v4.getName()));

        // Events...
        QVERIFY(ml.hasEvent(1));
        QVERIFY(ml.hasEvent(2));
        QVERIFY(ml.hasEvent(3));
        QVERIFY(ml.hasEvent(4));
        QVERIFY(ml.hasEvent(5));

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }

    {
        // Now, open log, make changes, and save again...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);

        QVERIFY(ml.removeAllEvents(v1.getName(), errMsg));
        QVERIFY(ml.getNLogEvents() == 1);   // SHould remove 4 out of 5...

        // Now save this...         (This should do replace)
        QVERIFY(ml.save(errMsg));

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }

    {
        // Now, open again, and ensure we have done a 'replace'
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 1);

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }
}

void MaintenanceLogUT::testClear()
{
    std::string errMsg;

    {   // First, create a fresh log to play with...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        addEventsToLog(ml, v1, v2);

        // Now save to disk (for use later)
        QVERIFY(ml.save(errMsg));
        QVERIFY(errMsg.empty());

        // Verify state...
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);
        QVERIFY(ml.isOpen());
        QVERIFY(ml.getLogFileName() == myLogFileName);
        QVERIFY(ml.logExists(myLogFileName));

        // Now clear...
        ml.clear();

        // And recheck state...
        QVERIFY(ml.getNVehicles() == 0);
        QVERIFY(ml.getNLogEvents() == 0);
        QVERIFY(ml.isOpen());                           // Current log still open, but now empty
        QVERIFY(ml.getLogFileName() == myLogFileName);  // Not changed...
        QVERIFY(ml.logExists(myLogFileName));           // Should not affect what's already been saved.

        ml.close();
    }

    {   // Now open what's on disk, and verify it hasn't been changed
        // (I.e. it was saved before the clear was done, and a save
        // was not done AFTER the save)
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));
        QVERIFY(ml.getNVehicles() == 0);
        QVERIFY(ml.getNLogEvents() == 0);

        QVERIFY(ml.openExistingLog(myLogFileName, errMsg));
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.getNLogEvents() == 5);

        // Now verify it contains all we expect...

        // Vehicles...
        QVERIFY(ml.hasVehicle(v1.getName()));
        QVERIFY(ml.hasVehicle(v2.getName()));
        QVERIFY(ml.hasVehicle(v3.getName()));
        QVERIFY(ml.hasVehicle(v4.getName()));

        // Events...
        QVERIFY(ml.hasEvent(1));
        QVERIFY(ml.hasEvent(2));
        QVERIFY(ml.hasEvent(3));
        QVERIFY(ml.hasEvent(4));
        QVERIFY(ml.hasEvent(5));

        ml.close();
        QVERIFY(checkIfClosed(ml));
    }
}

////////////////////////////
// ----- Vehicle tests -----
void MaintenanceLogUT::testAddVehicle()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;

    // No Log open yet...
    res = ml.addVehicle(v1, errMsg);
    QVERIFY(res == false);
    QVERIFY(!errMsg.empty());
    QVERIFY(errMsg == "MaintenanceLog::addVehicle: No file open yet.");
    QVERIFY(ml.getNVehicles() == 0);

    res = ml.createNewLog(myLogFileName, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNVehicles() == 0);

    res = ml.addVehicle(v1, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNVehicles() == 1);

    res = ml.addVehicle(v2, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNVehicles() == 2);

    // Try adding incomplete vehicle...
    Vehicle vInc;
    res = ml.addVehicle(vInc, errMsg);
    QVERIFY(res == false);
    QVERIFY(!errMsg.empty());
    QVERIFY(errMsg == "MaintenanceLog::addVehicle: Vehicle is incomplete. Not added.");
    QVERIFY(ml.getNVehicles() == 2);

    // Try adding same vehicle again...
    res = ml.addVehicle(v1, errMsg);
    QVERIFY(res == false);
    QVERIFY(!errMsg.empty());
    QVERIFY(errMsg == "MaintenanceLog::addVehicle: Vehicle 'Wayne's Car' already exists.");
    QVERIFY(ml.getNVehicles() == 2);

    // Proper management of errMsg. It should clear any existing text...
    errMsg = "Hopefully this gets cleared";
    Vehicle v5("Another Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    res = ml.addVehicle(v5, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNVehicles() == 3);
}

void MaintenanceLogUT::testGetVehicle()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);

    // Now get a copy of one...
    Vehicle v5;
    res = ml.getVehicle("The Toy", v5, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(v5 == v3);

    // Now try to fetch one that doesn't exist...
    res = ml.getVehicle("Should't find this one", v5, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    QVERIFY(v5 != v3);          // Should no longer match v3...
    QVERIFY(v5 == Vehicle());   // But instead, be a defaulted Vehicle..
}

void MaintenanceLogUT::testUpdateVehicle()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);

    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.hasVehicle("Work Truck") == true);

    // Get a copy of an existing one...
    Vehicle v5;
    res = ml.getVehicle("Work Truck", v5, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(v5.getModel() == "Blah");

    // Now change & update it...
    v5.setModel("Kahuna");  // Change any, or everything except name...

    res = ml.updateVehicle(v5, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.hasVehicle("Work Truck") == true);

    // Get it again, and verify it's changed...
    Vehicle v6;
    res = ml.getVehicle("Work Truck", v6, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(v6.getModel() == "Kahuna");

    // Now try to update a Vehicle that doesn't exist...
    v6.setName("Should't find this one");

    res = ml.updateVehicle(v6, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    QVERIFY(errMsg == "MaintenanceLog::updateVehicle: Vehicle 'Should't find this one' not found.");
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.hasVehicle("Work Truck") == true);
}

void MaintenanceLogUT::testRemoveVehicle()
{
    {   // Basic tests
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        bool res;
        std::string errMsg;

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);

        QVERIFY(ml.getNVehicles() == 4);
        QVERIFY(ml.hasVehicle("Work Truck") == true);

        // Remove one...
        res = ml.removeVehicle("Work Truck", errMsg);
        QVERIFY(res == true);
        QVERIFY(errMsg.empty());
        QVERIFY(ml.getNVehicles() == 3);
        QVERIFY(ml.hasVehicle("Work Truck") == false);

        // Now try to remove one with name that doesn't exist...
        res = ml.removeVehicle("Should't find this one", errMsg);
        QVERIFY(res == false);
        QVERIFY(errMsg.empty() == false);
        QVERIFY(errMsg == "MaintenanceLog::removeVehicle: Vehicle 'Should't find this one' not found.");
        QVERIFY(ml.getNVehicles() == 3);
    }

    {   // Now try to remove a Vehicle that's being used in some Events...
        MaintenanceLog ml;
        QVERIFY(checkIfClosed(ml));

        bool res;
        std::string errMsg;

        // Create and populate a log as starting point...
        ml.createNewLog(myLogFileName, errMsg);
        addVehiclesToLog(ml, v1, v2, v3, v4);
        addEventsToLog(ml, v1, v2);                     // Note only v1 & v2 used in Events...
        QVERIFY(ml.getNVehicles() == 4);

        QVERIFY(ml.hasVehicle("Work Truck") == true);   // v2
        QVERIFY(ml.hasVehicle("The Toy")    == true);   // v3

        // Try to remove one being used...
        res = ml.removeVehicle("Work Truck", errMsg);
        QVERIFY(res == false);
        QVERIFY(errMsg.empty() == false);
        QVERIFY(errMsg == "MaintenanceLog::removeVehicle: Vehicle 'Work Truck' is being used in Events. Not removed.");
        QVERIFY(ml.getNVehicles() == 4);                // Not removed...
        QVERIFY(ml.hasVehicle("Work Truck") == true);

        // Even with Events present, an unused one should still be able to be removed...
        res = ml.removeVehicle("The Toy", errMsg);
        QVERIFY(res == true);
        QVERIFY(errMsg.empty() == true);
        QVERIFY(ml.getNVehicles() == 3);                // Removed...
        QVERIFY(ml.hasVehicle("The Toy") == false);
    }
}

void MaintenanceLogUT::testHasVehicle()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);

    QVERIFY(ml.getNVehicles() == 4);

    // Test for all known ones..
    QVERIFY(ml.hasVehicle("Wayne's Car") == true);
    QVERIFY(ml.hasVehicle("Work Truck") == true);
    QVERIFY(ml.hasVehicle("The Toy") == true);
    QVERIFY(ml.hasVehicle("Another Car") == true);

    // None of these should be found...
    QVERIFY(ml.hasVehicle("THE TOY") == false);
    QVERIFY(ml.hasVehicle(" The Toy") == false);
    QVERIFY(ml.hasVehicle("The Toy ") == false);
    QVERIFY(ml.hasVehicle("") == false);
}

void MaintenanceLogUT::testIsVehicleUsed()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    addEventsToLog(ml, v1, v2);

    QVERIFY(ml.getNLogEvents() == 5);

    QVERIFY(ml.isVehicleUsed(v1.getName()) == true);
    QVERIFY(ml.isVehicleUsed(v2.getName()) == true);
    QVERIFY(ml.isVehicleUsed(v3.getName()) == false);
    QVERIFY(ml.isVehicleUsed(v4.getName()) == false);

    // Remove all Events associated with v1...
    ml.removeAllEvents(v1, errMsg);

    QVERIFY(ml.getNLogEvents() == 1);

    QVERIFY(ml.isVehicleUsed(v1.getName()) == false);
    QVERIFY(ml.isVehicleUsed(v2.getName()) == true);
    QVERIFY(ml.isVehicleUsed(v3.getName()) == false);
    QVERIFY(ml.isVehicleUsed(v4.getName()) == false);
}

void MaintenanceLogUT::testGetVehicles()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);

    const std::vector<Vehicle>& v = ml.getVehicles();

    QVERIFY(v.size() == 4);
    QVERIFY(v[0].getName() == v1.getName());
    QVERIFY(v[1].getName() == v2.getName());
    QVERIFY(v[2].getName() == v3.getName());
    QVERIFY(v[3].getName() == v4.getName());

    //v[0].setMake("Lambo"); // Shouldn't compile as it's a const reference...
}

//////////////////////////
// ----- Event tests -----
void MaintenanceLogUT::testAddEvent()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;
    std::string expectedResults;
    std::unique_ptr<ServiceEventBase> uPtr;

    // ---
    // Trying to addEvent before log opened should fail...
    uPtr.reset(new TireRotationEvent(33, "04/23/17", "Bonavista Esso", 135123,
                                     "Regular Spring/Autumn stuff.", 125));
    res = ml.addEvent(std::move(uPtr), v1, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::addEvent: No file open yet.";
    QVERIFY(errMsg == expectedResults);
    QVERIFY(uPtr == nullptr);

    // ---
    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);

    // ---
    // Typical, valid adds...
    uPtr.reset(new MiscEvent(1, "11/16/16", "Kramer Mazda", 134321,
                             "Replace front wipers.", 20));

    res = ml.addEvent(std::move(uPtr), v1, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNLogEvents() == 1);
    QVERIFY(uPtr == nullptr);

    uPtr.reset(new OilChangeEvent(2, "04/23/17", "Bonavista Esso", 135123,
                                  "Regular Spring/Autumn stuff.", 75));

    res = ml.addEvent(std::move(uPtr), v1, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNLogEvents() == 2);
    QVERIFY(uPtr == nullptr);

    uPtr.reset(new TireRotationEvent(3, "04/23/17", "Bonavista Esso", 135123,
                                     "Regular Spring/Autumn stuff.", 125));

    res = ml.addEvent(std::move(uPtr), v1, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNLogEvents() == 3);
    QVERIFY(uPtr == nullptr);

    uPtr.reset(new ScheduledMaintEvent(4, "04/23/17", "Bonavista Esso", 135123,
                                       "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                       20000, 18));

    res = ml.addEvent(std::move(uPtr), v1, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(uPtr == nullptr);

    // ---
    // Try to add with an incomplete Vehicle...
    Vehicle vInc;
    uPtr.reset(new TireRotationEvent(33, "04/23/17", "Bonavista Esso", 135123,
                                     "Regular Spring/Autumn stuff.", 125));
    res = ml.addEvent(std::move(uPtr), vInc, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::addEvent: Vehicle is incomplete. Not added.";
    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(uPtr == nullptr);

    // ---
    // Try to add an event with an id that already exists...
    uPtr.reset(new ScheduledMaintEvent(4, "04/23/17", "Bonavista Esso", 135123,
                                       "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                       20000, 18));
    res = ml.addEvent(std::move(uPtr), v1, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::addEvent: Event '4' already exists.";
    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(uPtr == nullptr);

    // ---
    // Try to add an event with a vehicle that doesn't exist in the log...
    Vehicle vBad = v1;
    vBad.setName("NotInLog");
    uPtr.reset(new ScheduledMaintEvent(44, "04/23/17", "Bonavista Esso", 135123,
                                       "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                       20000, 18));
    res = ml.addEvent(std::move(uPtr), vBad, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::addEvent: Vehicle 'NotInLog' is unknown. Not added.";
    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(uPtr == nullptr);

    // ---
    // Try to add an oil change to an Electric car...
    uPtr.reset(new OilChangeEvent(22, "04/23/17", "Bonavista Esso", 135123,
                                  "Regular Spring/Autumn stuff.", 75));

    res = ml.addEvent(std::move(uPtr), v3, errMsg);     // v3 is electric car...
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::addEvent: Oil Change not allowed for Electric vehicles. Not added.";;
    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(uPtr == nullptr);

    // ---
    // Try to add a nullptr event...
    res = ml.addEvent(std::move(uPtr), v3, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::addEvent: Event invalid (null). Not added.";
    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(uPtr == nullptr);
}

void MaintenanceLogUT::testGetEvent()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;
    std::string expectedResults;
    std::unique_ptr<ServiceEventBase> uCopy;
    std::unique_ptr<ServiceEventBase> uExpected;
    Vehicle vCopy;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);
    addEventsToLog(ml, v1, v2);
    QVERIFY(ml.getNLogEvents() == 5);

    QVERIFY(ml.hasEvent(2));

    // Create an event to test against...
    uExpected.reset(new OilChangeEvent(2, "04/23/17", "Bonavista Esso", 135123,
                                       "Regular Spring/Autumn stuff.", 75));

    // ---
    // Basic valid get...
    res = ml.getEvent(2, uCopy, vCopy, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());

    QVERIFY(*uCopy == *uExpected);
    QVERIFY(uCopy->getShop() == "Bonavista Esso");  // Base...

    // Method from derived class not avail through base (shouldn't compile)...
    //QVERIFY(uCopy->getRepeatOdom() == 3000);

    // ... but is with cast...
    QVERIFY(dynamic_cast<const OilChangeEvent&>(*uCopy).getRepeatOdom() == 3000);

    QVERIFY(vCopy == v1);                           // Verify vehicle...

    // Make sure we didn't change the log any...
    QVERIFY(ml.getNLogEvents() == 5);
    QVERIFY(ml.hasEvent(2));

    // ---
    // Try for an event which doesn't exist...
    QVERIFY(ml.hasEvent(222) == false);
    res = ml.getEvent(222, uCopy, vCopy, errMsg);      // Note also. uCopy still contains the above at this point
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::getEvent: Event '222' doesn't exist.";

    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 5);
    QVERIFY(uCopy == nullptr);                  // Should now be cleared...

    QVERIFY(vCopy == Vehicle());                // Verify output vehicle unset...
}

void MaintenanceLogUT::testUpdateEvent()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;
    std::unique_ptr<ServiceEventBase> uCopy;
    Vehicle vCopy;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);
    addEventsToLog(ml, v1, v2);
    QVERIFY(ml.getNLogEvents() == 5);

    // ---
    // Get an event and it's vehicle, fiddle with them and update...
    res = ml.getEvent(2, uCopy, vCopy, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());

    QVERIFY(uCopy->getNotes() != "Blown Engine!");
    uCopy->setNotes("Blown Engine!");
    QVERIFY(dynamic_cast<const OilChangeEvent&>(*uCopy).getRepeatOdom() == 3000);

    dynamic_cast<OilChangeEvent&>(*uCopy).setRepeatOdom(5555);
    QVERIFY(dynamic_cast<const OilChangeEvent&>(*uCopy).getRepeatOdom() == 5555);

    res = ml.updateEvent(std::move(uCopy), vCopy, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());

    // Verify changed by looking for changes in output listing...
    std::stringstream ss;
    ml.listAllEvents(ss);
    QVERIFY(ss.str().find("EVENT,2,Oil Change,04/23/17,Bonavista Esso,135123,Blown Engine!,") != std::string::npos);

    // @TODO - add tests for:
    // null event pass in...
    // incomplete vehicle...
    // Vehicle doesn't exist in log...
    // Event id not found in log...
}

void MaintenanceLogUT::testRemoveEvent()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;
    std::string expectedResults;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);
    addEventsToLog(ml, v1, v2);
    QVERIFY(ml.getNLogEvents() == 5);

    // ---
    // Basic, valid remove...
    QVERIFY(ml.hasEvent(2));
    res = ml.removeEvent(2, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNLogEvents() == 4);
    QVERIFY(ml.hasEvent(2) == false);

    // ---
    // try on non-existing event...
    res = ml.removeEvent(2, errMsg);
    QVERIFY(res == false);
    QVERIFY(errMsg.empty() == false);
    expectedResults = "MaintenanceLog::removeEvent: Event '2' doesn't exist.";
    QVERIFY(errMsg == expectedResults);
    QVERIFY(ml.getNLogEvents() == 4);
}

void MaintenanceLogUT::testRemoveAllEventsByVehicle()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    bool res;
    std::string errMsg;
    std::string expectedResults;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);
    addEventsToLog(ml, v1, v2);
    QVERIFY(ml.getNLogEvents() == 5);

    // ---
    // Basic, valid remove...
    res = ml.removeAllEvents(v1, errMsg);
    QVERIFY(res == true);
    QVERIFY(errMsg.empty());
    QVERIFY(ml.getNLogEvents() == 1);       // 4 of the 5 should have been removed...
    QVERIFY(ml.hasEvent(1) == false);
    QVERIFY(ml.hasEvent(2) == false);
    QVERIFY(ml.hasEvent(3) == true);
    QVERIFY(ml.hasEvent(4) == false);
    QVERIFY(ml.hasEvent(5) == false);

    // @TODO - Add more tests...
}

void MaintenanceLogUT::testHasEvent()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);
    addEventsToLog(ml, v1, v2);
    QVERIFY(ml.getNLogEvents() == 5);

    QVERIFY(ml.hasEvent(1));
    QVERIFY(ml.hasEvent(3));
    QVERIFY(ml.hasEvent(5));
    QVERIFY(ml.hasEvent(217) == false);
}

void MaintenanceLogUT::testGetEvents()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    addEventsToLog(ml, v1, v2);

    const std::vector< std::pair< std::unique_ptr<ServiceEventBase>, Vehicle > >& v = ml.getEvents();

    QVERIFY(v.at(0).first->getId() == 1);
    QVERIFY(v.at(1).first->getId() == 2);
    QVERIFY(v.at(2).first->getId() == 3);
    QVERIFY(v.at(3).first->getId() == 4);
    QVERIFY(v.at(4).first->getId() == 5);
}

void MaintenanceLogUT::testListAllEvents()
{
    MaintenanceLog ml;
    QVERIFY(checkIfClosed(ml));

    std::string errMsg;

    // Create and populate a log as starting point...
    ml.createNewLog(myLogFileName, errMsg);
    addVehiclesToLog(ml, v1, v2, v3, v4);
    QVERIFY(ml.getNVehicles() == 4);
    QVERIFY(ml.getNLogEvents() == 0);
    addEventsToLog(ml, v1, v2);
    QVERIFY(ml.getNLogEvents() == 5);

    std::stringstream ss;
    ml.listAllEvents(ss);

    QVERIFY(ss.str().size() > 300);         // @TODO - Improve the verifications here...
}

///////////////////////
// Internal helper funcs...
bool MaintenanceLogUT::checkIfClosed(const MaintenanceLog& ml)
{
    return ml.getLogFileName().empty()
        && ml.getNVehicles() == 0
        && ml.getNLogEvents() == 0
        && !ml.isOpen();
}

bool MaintenanceLogUT::addVehiclesToLog(MaintenanceLog& ml,
                                        const Vehicle& v1, const Vehicle& v2,
                                        const Vehicle& v3, const Vehicle& v4)
{
    std::string errMsg;

    // Add vehicles...
    ml.addVehicle(v1, errMsg);
    ml.addVehicle(v2, errMsg);
    ml.addVehicle(v3, errMsg);
    ml.addVehicle(v4, errMsg);

    return true;
}
bool MaintenanceLogUT::addEventsToLog(MaintenanceLog& ml, const Vehicle& v1, const Vehicle& v2)
{
    std::string errMsg;

    std::unique_ptr<ServiceEventBase> uPtr;

    uPtr.reset(new MiscEvent(1, "11/16/16", "Kramer Mazda", 134321,
                             "Replace front wipers.", 20));
    ml.addEvent(std::move(uPtr), v1, errMsg);

    uPtr.reset(new OilChangeEvent(2, "04/23/17", "Bonavista Esso", 135123,
                                  "Regular Spring/Autumn stuff.", 75));
    ml.addEvent(std::move(uPtr), v1, errMsg);


    uPtr.reset(new TireRotationEvent(3, "04/23/17", "Bonavista Esso", 135123,
                                     "Regular Spring/Autumn stuff.", 125));
    ml.addEvent(std::move(uPtr), v2, errMsg);                                          // Different car


    uPtr.reset(new ScheduledMaintEvent(4, "04/23/17", "Bonavista Esso", 135123,
                                       "Coolant flushed.", 60, ScheduledMaintTypes::COOLANT_FLUSH,
                                       20000, 18));
    ml.addEvent(std::move(uPtr), v1, errMsg);

    uPtr.reset(new OilChangeEvent(5, "10/06/17", "Bonavista Esso", 137321,          // Second oil change...
                                  "Autumn stuff.", 75));
    ml.addEvent(std::move(uPtr), v1, errMsg);

    return true;
}
//////////////// End Test Helper Funcs /////////////
