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
    QVERIFY(pf.validateInputGrid());
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
//    QVERIFY(pf.validateInputGrid() == false);
//    QVERIFY(pf.getNRows() == 0);
//    QVERIFY(pf.getNCols() == 0);
//    QVERIFY(pf.getTotalLength() == (pf.getNRows()*pf.getNCols()));

//    std::pair<int,int> src = pf.getSourceNode();
//    std::pair<int,int> tgt = pf.getTargetNode();

//    QVERIFY(src.first == -1 && src.second == -1);
//    QVERIFY(tgt.first == -1 && tgt.second == -1);
}
