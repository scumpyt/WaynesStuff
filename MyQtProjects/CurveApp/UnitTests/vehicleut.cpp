#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include <sstream>
#include <iostream>

#include "vehicleut.h"
#include "vehicle.h"

VehicleUT::VehicleUT()
{

}

void VehicleUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void VehicleUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void VehicleUT::init()
{
    // Runs before each test...
}

void VehicleUT::cleanup()
{
    // Runs at the end of each test...
}

void VehicleUT::testCtor()
{
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);
    QVERIFY(v1.getName()        == "Wayne's Car");
    QVERIFY(v1.getMake()        == "Mazda");
    QVERIFY(v1.getModel()       == "CX9");
    QVERIFY(v1.getYear()        == "2010");
    QVERIFY(v1.getOdom()        == 137456);
    QVERIFY(v1.getVehicleType() == VehicleTypes::DIESEL);
    QVERIFY(v1.isComplete() == true);

    Vehicle v2("Work Truck","Lexus","Blah","2004");
    QVERIFY(v2.getName()        == "Work Truck");
    QVERIFY(v2.getMake()        == "Lexus");
    QVERIFY(v2.getModel()       == "Blah");
    QVERIFY(v2.getYear()        == "2004");
    QVERIFY(v2.getOdom()        == -1);
    QVERIFY(v2.getVehicleType() == VehicleTypes::GAS);
    QVERIFY(v2.isComplete() == false);  // Odom not set yet

    Vehicle v3;               // fully defaulted...
    QVERIFY(v3.getName().empty());
    QVERIFY(v3.getMake().empty());
    QVERIFY(v3.getModel().empty());
    QVERIFY(v3.getYear().empty());
    QVERIFY(v3.getOdom()        == -1);
    QVERIFY(v3.getVehicleType() == VehicleTypes::GAS);
    QVERIFY(v3.isComplete() == false);  // Odom not set yet
}

void VehicleUT::testCopyAndAssignment()
{
    Vehicle vOrig1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    Vehicle v1(vOrig1);

    QVERIFY(v1.getName()        == "Wayne's Car");
    QVERIFY(v1.getMake()        == "Mazda");
    QVERIFY(v1.getModel()       == "CX9");
    QVERIFY(v1.getYear()        == "2010");
    QVERIFY(v1.getOdom()        == 137456);
    QVERIFY(v1.getVehicleType() == VehicleTypes::DIESEL);
    QVERIFY(v1.isComplete()     == vOrig1.isComplete());

    Vehicle vOrig2("Work Truck","Lexus","Blah","2004");

    Vehicle v2 = vOrig2;
    QVERIFY(v2.getName()        == "Work Truck");
    QVERIFY(v2.getMake()        == "Lexus");
    QVERIFY(v2.getModel()       == "Blah");
    QVERIFY(v2.getYear()        == "2004");
    QVERIFY(v2.getOdom()        == -1);
    QVERIFY(v2.getVehicleType() == VehicleTypes::GAS);
    QVERIFY(v2.isComplete()     == vOrig2.isComplete());
}

void VehicleUT::testPrintOper1()
{
    // Test 1 - typical
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);

    // Use the operator<< to write to a string...
    std::stringstream ss;
    ss << v1;

    std::string expectedResults = "VEHICLE,Wayne's Car,Mazda,CX9,2010,137456,DIESEL,";

    QVERIFY(ss.str() == expectedResults);
}

void VehicleUT::testPrintOper2()
{
    // Test 2 - defaulted
    Vehicle v1;

    // Use the operator<< to write to a string...
    std::stringstream ss;
    ss << v1;

    std::string expectedResults = "VEHICLE,,,,,-1,GAS,";

    QVERIFY(ss.str() == expectedResults);
}

void VehicleUT::testCompareOpers()
{
    Vehicle v1("Wayne's Car","Mazda","CX9","2010",137456,VehicleTypes::DIESEL);
    Vehicle v2("Work Truck","Lexus","Blah","2004");
    Vehicle v3 = v1;
    Vehicle v4 = v2;

    QVERIFY(v1 == v3);
    QVERIFY(v3 == v1);
    QVERIFY(v1 != v2);
    QVERIFY(v2 != v1);

    QVERIFY(v2 == v4);
    QVERIFY(v4 == v2);
    QVERIFY(v2 != v3);
    QVERIFY(v3 != v2);

    QVERIFY(v1 == v1);  // compare to self...

    Vehicle v5 = v2;
    v5.setOdom(123456);
    QVERIFY(v5 == v2);  // Comparison disregards odometer!!!

    Vehicle v6,v7;

    QVERIFY(v6 == v7);  // Completely defaulted should still work...
}
