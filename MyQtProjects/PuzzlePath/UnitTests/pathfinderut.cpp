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

void PathFinderUT::testIsValidChar()
{
    PathFinder pf(inGrid);

    QVERIFY(pf.isValidChar(0)  == false);   // Top row all X's
    QVERIFY(pf.isValidChar(9)  == false);
    QVERIFY(pf.isValidChar(10) == false);   // Second Row - all but edges
    QVERIFY(pf.isValidChar(11) == true);
    QVERIFY(pf.isValidChar(12) == true);
    QVERIFY(pf.isValidChar(13) == true);
    QVERIFY(pf.isValidChar(14) == true);
    QVERIFY(pf.isValidChar(15) == true);
    QVERIFY(pf.isValidChar(16) == true);
    QVERIFY(pf.isValidChar(17) == true);
    QVERIFY(pf.isValidChar(18) == true);
    QVERIFY(pf.isValidChar(19) == false);
    QVERIFY(pf.isValidChar(20) == false);   // Third row...
    QVERIFY(pf.isValidChar(21) == true);

    QVERIFY(pf.isValidChar(21222) == false);    // index out of range tests
    QVERIFY(pf.isValidChar(-14) == false);
}

void PathFinderUT::testBuildEdgeGraph()
{
//    PathFinder pf(inGrid);
//    //pf.printInGrid();
//    //QVERIFY (1 == 0);

//    std::vector< std::vector<edge> > theEdges = pf.buildEdgeGraph();

//    QVERIFY (theEdges.size() == pf.getTotalLength()); // Should have as many nodes as inGrid...
}
