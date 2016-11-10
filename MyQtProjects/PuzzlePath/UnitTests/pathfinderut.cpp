#include <QtTest/QtTest>
#include <QSignalSpy>
//#include <qstring.h>

#include <iostream>
#include <fstream>

#include "pathfinder.h"
#include "pathfinderut.h"

PathFinderUT::PathFinderUT()
{

}

void PathFinderUT::initTestCase()
{
    // Runs once, at the beginning of all tests...
}

void PathFinderUT::cleanupTestCase()
{
    // Runs once, at the end of all tests...
}

void PathFinderUT::init()
{
    // Runs before each test...

    // Read Puzzle1.txt as a default test
    std::string curLine;

    std::ifstream inFile ("../../Puzzle1.txt");
    QVERIFY (inFile.is_open());

    while (std::getline (inFile, curLine))
    {
        inGrid.emplace_back(curLine);
        //std::cout << *(inGrid.end()-1) << "\n";
    }
    inFile.close();
}

void PathFinderUT::cleanup()
{
    // Runs at the end of each test...
    inGrid.clear();
}

void PathFinderUT::testBasics1()
{
    // Using default Puzzle1.txt
    PathFinder pf(inGrid);
    QVERIFY(pf.validateInputFile());
    QVERIFY(pf.getNRows() == 4);
    QVERIFY(pf.getNCols() == 10);
    QVERIFY(pf.getTotalLength() == (pf.getNRows()*pf.getNCols()));

    std::pair<int,int> src = pf.getSourceNode();
    std::pair<int,int> tgt = pf.getTargetNode();

    QVERIFY(src.first == 1 && src.second == 3);
    QVERIFY(tgt.first == 2 && tgt.second == 1);
}

void PathFinderUT::testBasics2()
{
    // Using empty inGrid...
    std::vector<std::string> emptyGrid;
    PathFinder pf(emptyGrid);
    QVERIFY(pf.validateInputFile() == false);
    QVERIFY(pf.getNRows() == 0);
    QVERIFY(pf.getNCols() == 0);
    QVERIFY(pf.getTotalLength() == (pf.getNRows()*pf.getNCols()));

    std::pair<int,int> src = pf.getSourceNode();
    std::pair<int,int> tgt = pf.getTargetNode();

    QVERIFY(src.first == -1 && src.second == -1);
    QVERIFY(tgt.first == -1 && tgt.second == -1);
}

void PathFinderUT::testFindNode()
{
    PathFinder pf(inGrid);

    int r, c;
    QVERIFY(pf.findNode('A', r, c) == true);
    QVERIFY(r == 1 && c == 3);

    QVERIFY(pf.findNode('B', r, c) == true);
    QVERIFY(r == 2 && c == 1);

    QVERIFY(pf.findNode('a', r, c) == false);
    QVERIFY(r == -1 && c == -1);

    std::vector<std::string> emptyGrid;
    PathFinder pf2(emptyGrid);

    QVERIFY(pf2.findNode('X', r, c) == false);
    QVERIFY(r == -1 && c == -1);
}

void PathFinderUT::testGetChar()
{
    PathFinder pf(inGrid);
    QVERIFY(pf.getChar(0,0) == 'X');
    QVERIFY(pf.getChar(1,3) == 'A');
    QVERIFY(pf.getChar(2,1) == 'B');

    // Out of range returns an 'X'
    QVERIFY(pf.getChar(1000, 2000) == 'X');
}

void PathFinderUT::testSearchNode()
{
    PathFinder pf(inGrid);

    QVERIFY(pf.searchNode(1,3,12345) == false);
    pf.setGridNode(1,3,12345);
    QVERIFY(pf.searchNode(1,3,12345) == true);
}
