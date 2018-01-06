#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include <sstream>
#include <iostream>

#include "misceventut.h"
#include "miscevent.h"

MiscEventUT::MiscEventUT()
{

}

void MiscEventUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void MiscEventUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void MiscEventUT::init()
{
    // Runs before each test...
}

void MiscEventUT::cleanup()
{
    // Runs at the end of each test...
}

void MiscEventUT::testCtor()
{
    {
        MiscEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                      "Regular Spring/Autumn stuff.", 75.50);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getName()           == "Misc Event");
        QVERIFY(oc1.getReminderString().empty());
    }

    {
        MiscEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                      "Regular Spring/Autumn stuff.", 75.50);

        QVERIFY(oc1.getId()             == 1);
        QVERIFY(oc1.getDate()           == "04/23/17");
        QVERIFY(oc1.getShop()           == "Bonavista Esso");
        QVERIFY(oc1.getOdom()           == 135123);
        QVERIFY(oc1.getNotes()          == "Regular Spring/Autumn stuff.");
        QVERIFY(oc1.getPreTaxCost()     == 75.50);

        QVERIFY(oc1.getName()           == "Misc Event");
        QVERIFY(oc1.getReminderString().empty());
    }
}

void MiscEventUT::testCompareOper()
{
    MiscEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                  "Regular Spring/Autumn stuff.", 75.50);
    MiscEvent oc2 = oc1;

    QVERIFY(oc1 == oc2);

    oc2.setShop("Of Horrors");
    QVERIFY(oc1 != oc2);
}

void MiscEventUT::testPrintOper()
{
    MiscEvent oc1(1, "04/23/17", "Bonavista Esso", 135123,
                  "Regular Spring/Autumn stuff.", 75.50);

    // Use the operator<< to write to a string...
    std::stringstream ss;
    ss << oc1;

    std::string expectedResults = "EVENT,1,Misc Event,04/23/17,Bonavista Esso,135123,Regular Spring/Autumn stuff.,75.5,";
    QVERIFY(ss.str() == expectedResults);
}
