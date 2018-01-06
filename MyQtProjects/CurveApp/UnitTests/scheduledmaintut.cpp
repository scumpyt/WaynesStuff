#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include <sstream>
#include <iostream>

#include "scheduledmaintut.h"
#include "scheduledmaintevent.h"

ScheduledMaintUT::ScheduledMaintUT()
{

}

void ScheduledMaintUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void ScheduledMaintUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void ScheduledMaintUT::init()
{
    // Runs before each test...
}

void ScheduledMaintUT::cleanup()
{
    // Runs at the end of each test...
}

void ScheduledMaintUT::testCtor()
{
    {
        ScheduledMaintEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                                "Regular Spring/Autumn stuff.", 75.50,
                                ScheduledMaintTypes::CABIN_AIR_FILTER,
                                40000, 24);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getMaintType()      == ScheduledMaintTypes::CABIN_AIR_FILTER);
        QVERIFY(oc1.getRepeatOdom()     == 40000);
        QVERIFY(oc1.getRepeatMonths()   == 24);

        QVERIFY(oc1.getName()           == "Scheduled Event");
        QVERIFY(oc1.getReminderString() == "Repeat in: 40000 kms or 24 mths");
    }

    {
        ScheduledMaintEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                                "Regular Spring/Autumn stuff.", 75.50,
                                ScheduledMaintTypes::COOLANT_FLUSH,
                                15000, 18);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getMaintType()      == ScheduledMaintTypes::COOLANT_FLUSH);
        QVERIFY(oc1.getRepeatOdom()     == 15000);
        QVERIFY(oc1.getRepeatMonths()   == 18);

        QVERIFY(oc1.getName()           == "Scheduled Event");
        QVERIFY(oc1.getReminderString() == "Repeat in: 15000 kms or 18 mths");
    }
}

void ScheduledMaintUT::testCompareOper()
{
    ScheduledMaintEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                            "Regular Spring/Autumn stuff.", 75.50,
                            ScheduledMaintTypes::COOLANT_FLUSH,
                            15000, 18);
    ScheduledMaintEvent oc2 = oc1;

    QVERIFY(oc1 == oc2);

    oc2.setShop("Of Horrors");
    QVERIFY(oc1 != oc2);
}


void ScheduledMaintUT::testPrintOper()
{
    ScheduledMaintEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                            "Regular Spring/Autumn stuff.", 75.50,
                            ScheduledMaintTypes::COOLANT_FLUSH,
                            15000, 18);

    // Use the operator<< to write to a string...
    std::stringstream ss;
    ss << oc1;

    std::string expectedResults = "EVENT,1,Scheduled Event,04/23/17,Bonavista Esso,135123,Regular Spring/Autumn stuff.,75.5,15000,18,COOLANT_FLUSH,";

    QVERIFY(ss.str() == expectedResults);
}
