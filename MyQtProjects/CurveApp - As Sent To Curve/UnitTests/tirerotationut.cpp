#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include <sstream>
#include <iostream>

#include "tirerotationut.h"
#include "tirerotationevent.h"

TireRotationUT::TireRotationUT()
{

}

void TireRotationUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void TireRotationUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void TireRotationUT::init()
{
    // Runs before each test...
}

void TireRotationUT::cleanup()
{
    // Runs at the end of each test...
}

void TireRotationUT::testCtor()
{
    {
        TireRotationEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                           "Regular Spring/Autumn stuff.", 75.50);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getRepeatOdom()     == 10000);
        QVERIFY(oc1.getRepeatMonths()   == 12);

        QVERIFY(oc1.getName()           == "Tire Rotation");
        QVERIFY(oc1.getReminderString() == "Repeat in: 10000 kms or 12 mths");
    }

    {
        TireRotationEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                           "Regular Spring/Autumn stuff.", 75.50, 15000, 18);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getRepeatOdom()     == 15000);
        QVERIFY(oc1.getRepeatMonths()   == 18);

        QVERIFY(oc1.getName()           == "Tire Rotation");
        QVERIFY(oc1.getReminderString() == "Repeat in: 15000 kms or 18 mths");
    }
}

void TireRotationUT::testCompareOper()
{
    TireRotationEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                            "Regular Spring/Autumn stuff.", 75.50);
    TireRotationEvent oc2 = oc1;

    QVERIFY(oc1 == oc2);

    oc2.setShop("Of Horrors");
    QVERIFY(oc1 != oc2);
}

void TireRotationUT::testPrintOper()
{
    TireRotationEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                          "Regular Spring/Autumn stuff.", 75.50);

    // Use the operator<< to write to a string...
    std::stringstream ss;
    ss << oc1;

    //std::string expectedResults = "EVENT,1,Tire Rotation,04/23/17,Bonavista Esso,135123,Regular Spring/Autumn stuff.,75.5,Repeat in: 10000 kms or 12 mths,";
    std::string expectedResults = "EVENT,1,Tire Rotation,04/23/17,Bonavista Esso,135123,Regular Spring/Autumn stuff.,75.5,10000,12,";

    QVERIFY(ss.str() == expectedResults);
}
