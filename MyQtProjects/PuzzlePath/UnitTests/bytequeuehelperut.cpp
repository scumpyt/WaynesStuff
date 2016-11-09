#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QDebug>

#include "bytequeuehelperut.h"
#include "bytequeuehelper.h"

ByteQueueHelperUT::ByteQueueHelperUT()
{

}

void ByteQueueHelperUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void ByteQueueHelperUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void ByteQueueHelperUT::init()
{
    // Runs before each test...
}

void ByteQueueHelperUT::cleanup()
{
    // Runs at the end of each test...
}

void ByteQueueHelperUT::testPrintQueue()
{
    ByteQueueHelper bqh;
    bqh.printQueue();
    QVERIFY(1 == 0);
}
