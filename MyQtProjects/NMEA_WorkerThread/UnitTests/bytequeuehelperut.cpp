#include <QtTest/QtTest>
#include <QSignalSpy>

#include <iostream>

#include <string>

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
    //QVERIFY(1 == 0);
}

void ByteQueueHelperUT::testQAppend()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result { '1','2','3' };
    std::deque<unsigned char> toAdd  { '4','5','6' };

    bqh.qAppend(result, toAdd);

    QVERIFY(result.size() == 6);

    QVERIFY(result.at(0) ==  '1');
    QVERIFY(result.at(1) ==  '2');
    QVERIFY(result.at(2) ==  '3');
    QVERIFY(result.at(3) ==  '4');
    QVERIFY(result.at(4) ==  '5');
    QVERIFY(result.at(5) ==  '6');

    toAdd[0] = (unsigned char)'0x0D';   // Carriage return
    toAdd[1] = (unsigned char)'0x0A';   // Linefeed

    bqh.qAppend(result, toAdd);

    QVERIFY(result.size() == 9);

    QVERIFY(result.at(0) ==  '1');
    QVERIFY(result.at(1) ==  '2');
    QVERIFY(result.at(2) ==  '3');
    QVERIFY(result.at(3) ==  '4');
    QVERIFY(result.at(4) ==  '5');
    QVERIFY(result.at(5) ==  '6');
    QVERIFY(result.at(6) ==  (unsigned char)'0x0D');
    QVERIFY(result.at(7) ==  (unsigned char)'0x0A');
    QVERIFY(result.at(8) ==  '6');

    static const char* charBuf = "xyz";

    bqh.qAppend(result, charBuf, 3);

    QVERIFY(result.size() == 12);

    QVERIFY(result.at(0)  ==  '1');
    QVERIFY(result.at(1)  ==  '2');
    QVERIFY(result.at(2)  ==  '3');
    QVERIFY(result.at(3)  ==  '4');
    QVERIFY(result.at(4)  ==  '5');
    QVERIFY(result.at(5)  ==  '6');
    QVERIFY(result.at(6)  ==  (unsigned char)'0x0D');
    QVERIFY(result.at(7)  ==  (unsigned char)'0x0A');
    QVERIFY(result.at(8)  ==  '6');
    QVERIFY(result.at(9)  ==  (unsigned char)'x');
    QVERIFY(result.at(10) ==  (unsigned char)'y');
    QVERIFY(result.at(11) ==  (unsigned char)'z');

    result.clear();

    std::string str = "ABC";

    bqh.qAppend(result, str.c_str(), str.size());

    QVERIFY(result.size() == str.size());

    QVERIFY(result.at(0)  ==  'A');
    QVERIFY(result.at(1)  ==  'B');
    QVERIFY(result.at(2)  ==  'C');
}

void ByteQueueHelperUT::testQClear()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;
    std::deque<unsigned char> toAdd  { '1','2','3' };

    bqh.qAppend(result, toAdd);

    QVERIFY(result.size() == 3);

    QVERIFY(result.at(0)  ==  '1');
    QVERIFY(result.at(1)  ==  '2');
    QVERIFY(result.at(2)  ==  '3');

    bqh.qClear(result);
    QVERIFY(result.size() == 0);
}

void ByteQueueHelperUT::testQRemove()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;

    static const char* charBuf = "abc123xyz";

    bqh.qAppend(result, charBuf, 9);

    QVERIFY(result.size() == 9);

    QVERIFY(result.at(0)  ==  'a');
    QVERIFY(result.at(1)  ==  'b');
    QVERIFY(result.at(2)  ==  'c');
    QVERIFY(result.at(3)  ==  '1');
    QVERIFY(result.at(4)  ==  '2');
    QVERIFY(result.at(5)  ==  '3');
    QVERIFY(result.at(6)  ==  'x');
    QVERIFY(result.at(7)  ==  'y');
    QVERIFY(result.at(8)  ==  'z');

    bqh.qRemove(result, 3, 3);

    QVERIFY(result.size() == 6);

    QVERIFY(result.at(0)  ==  'a');
    QVERIFY(result.at(1)  ==  'b');
    QVERIFY(result.at(2)  ==  'c');
    QVERIFY(result.at(3)  ==  'x');
    QVERIFY(result.at(4)  ==  'y');
    QVERIFY(result.at(5)  ==  'z');
}


void ByteQueueHelperUT::testQSize()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;

    static const char* charBuf = "abc123xyz";

    bqh.qAppend(result, charBuf, 9);

    QVERIFY(result.size() == 9);
    QVERIFY(bqh.qSize(result) == 9);

    bqh.qRemove(result, 3, 3);

    QVERIFY(bqh.qSize(result) == 6);

    bqh.qRemove(result, 0, 6);

    QVERIFY(bqh.qSize(result) == 0);
}

void ByteQueueHelperUT::testIsQueueEmpty()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;

    QVERIFY(bqh.isQueueEmpty(result) == true);

    static const char* charBuf = "abc123xyz";

    bqh.qAppend(result, charBuf, 9);

    QVERIFY(result.size() == 9);
    QVERIFY(bqh.qSize(result) == 9);

    QVERIFY(bqh.isQueueEmpty(result) == false);

    bqh.qRemove(result, 3, 3);

    QVERIFY(bqh.qSize(result) == 6);
    QVERIFY(bqh.isQueueEmpty(result) == false);

    bqh.qRemove(result, 0, 6);

    QVERIFY(bqh.qSize(result) == 0);
    QVERIFY(bqh.isQueueEmpty(result) == true);
}

void ByteQueueHelperUT::testQMid()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;
    static const char* charBuf = "abc123xyz";
    bqh.qAppend(result, charBuf, 9);

    QVERIFY(result.size() == 9);

    QVERIFY(result.at(0)  ==  'a');
    QVERIFY(result.at(1)  ==  'b');
    QVERIFY(result.at(2)  ==  'c');
    QVERIFY(result.at(3)  ==  '1');
    QVERIFY(result.at(4)  ==  '2');
    QVERIFY(result.at(5)  ==  '3');
    QVERIFY(result.at(6)  ==  'x');
    QVERIFY(result.at(7)  ==  'y');
    QVERIFY(result.at(8)  ==  'z');

    std::deque<unsigned char> out = bqh.qMid(result, 3, 3);

    QVERIFY(result.size() == 9);        // Shouldn't change...

    QVERIFY(out.size() == 3);

    QVERIFY(out.at(0)  ==  '1');
    QVERIFY(out.at(1)  ==  '2');
    QVERIFY(out.at(2)  ==  '3');
}

void ByteQueueHelperUT::testQAt()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;
    static const char* charBuf = "abc123xyz";
    bqh.qAppend(result, charBuf, 9);

    QVERIFY(bqh.qAt(result, 0) == 'a');
    QVERIFY(bqh.qAt(result, 3) == '1');
    QVERIFY(bqh.qAt(result, 6) == 'x');

    QVERIFY_EXCEPTION_THROWN (bqh.qAt(result, 234), std::out_of_range);

    // -- OR -- to not use QT to verify...
    bool shouldNotGetHere = true;
    try
    {
        bqh.qAt(result, 234);
        shouldNotGetHere = true;
    }
    catch(const std::out_of_range&)
    {
        shouldNotGetHere = false;
    }
    QVERIFY(shouldNotGetHere == false);
}

void ByteQueueHelperUT::testQIndexOf()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;
    static const char* charBuf = "abc123xyz";
    bqh.qAppend(result, charBuf, 9);

    int indx;
    indx = bqh.qIndexOf(result, '1');
    QVERIFY(indx == 3);

    indx = bqh.qIndexOf(result, 'g');
    QVERIFY(indx == -1);

    indx = bqh.qIndexOf(result, '1', 2);
    QVERIFY(indx == 1);

    indx = bqh.qIndexOf(result, '1', 3);
    QVERIFY(indx == 0);

    indx = bqh.qIndexOf(result, '1', 4);
    QVERIFY(indx == -1);
}

void ByteQueueHelperUT::testQIndexOf_2()
{
    ByteQueueHelper bqh;
    std::deque<unsigned char> result;
    static const char* charBuf = "abc123xyz";
    bqh.qAppend(result, charBuf, 9);

    std::deque<unsigned char> matchBuf1;
    static const char* mBuf1 = "123";
    bqh.qAppend(matchBuf1, mBuf1, 3);

    std::deque<unsigned char> matchBuf2;
    static const char* mBuf2 = "Nope";
    bqh.qAppend(matchBuf2, mBuf2, 4);

    int indx;
    indx = bqh.qIndexOf(result, matchBuf1);
    QVERIFY(indx == 3);

    indx = bqh.qIndexOf(result, matchBuf2);
    QVERIFY(indx == -1);

    indx = bqh.qIndexOf(result, matchBuf1, 2);
    QVERIFY(indx == 1);

    indx = bqh.qIndexOf(result, matchBuf1, 3);
    QVERIFY(indx == 0);

    indx = bqh.qIndexOf(result, matchBuf1, 4);
    QVERIFY(indx == -1);
}

