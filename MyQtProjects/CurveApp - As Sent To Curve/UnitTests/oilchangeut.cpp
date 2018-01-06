#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include <sstream>
#include <iostream>

#include "oilchangeut.h"
#include "oilchangeevent.h"

OilChangeUT::OilChangeUT()
{

}

void OilChangeUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void OilChangeUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void OilChangeUT::init()
{
    // Runs before each test...
}

void OilChangeUT::cleanup()
{
    // Runs at the end of each test...
}

void OilChangeUT::testCtor()
{
    {
        OilChangeEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                           "Regular Spring/Autumn stuff.", 75.50);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getRepeatOdom()     == 3000);
        QVERIFY(oc1.getRepeatMonths()   == 6);

        QVERIFY(oc1.getName()           == "Oil Change");
        QVERIFY(oc1.getReminderString() == "Repeat in: 3000 kms or 6 mths");
    }

    {
        OilChangeEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                           "Regular Spring/Autumn stuff.", 75.50, 6000, 12);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getRepeatOdom()     == 6000);
        QVERIFY(oc1.getRepeatMonths()   == 12);

        QVERIFY(oc1.getName()           == "Oil Change");
        QVERIFY(oc1.getReminderString() == "Repeat in: 6000 kms or 12 mths");
    }
}

void OilChangeUT::testCompareOper()
{
    OilChangeEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                            "Regular Spring/Autumn stuff.", 75.50);
    OilChangeEvent oc2 = oc1;

    QVERIFY(oc1 == oc2);

    oc2.setShop("Of Horrors");
    QVERIFY(oc1 != oc2);
}

void OilChangeUT::testPrintOper()
{
    OilChangeEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                       "Regular Spring/Autumn stuff.", 75.50);

    // Use the operator<< to write to a string...
    std::stringstream ss;
    ss << oc1;

    std::string expectedResults = "EVENT,1,Oil Change,04/23/17,Bonavista Esso,135123,Regular Spring/Autumn stuff.,75.5,3000,6,";

    QVERIFY(ss.str() == expectedResults);
}
