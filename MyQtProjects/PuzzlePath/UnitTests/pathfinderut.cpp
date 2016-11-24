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

void PathFinderUT::testValidateInputFile1()
{
    PathFinder pf(inGrid);
    QVERIFY(pf.validateInputFile());
}

void PathFinderUT::testValidateInputFile2()
{
    std::vector<std::string> file;
    file.emplace_back(std::string("X X X"));
    file.emplace_back(std::string("X XAX"));
    file.emplace_back(std::string("X X X"));
    file.emplace_back(std::string("X X X"));
    file.emplace_back(std::string("X X X"));

    PathFinder pf (file);
    QVERIFY(pf.validateInputFile() == false);   // No target
}

void PathFinderUT::testExtractPath1()
{
    PathFinder pf(inGrid);
    std::vector<std::pair<int,int>> outPath = pf.extractPath();
    QVERIFY(outPath.size() == 2);

    // There are 2, equal possibilities here...
    // Path is going target to source
    bool match = false;
    if ( (outPath.at(0).first == 2 && outPath.at(0).second == 2) &&
         (outPath.at(1).first == 2 && outPath.at(1).second == 3) )
    {
        match = true;
    }

    if (!match &&
        (outPath.at(0).first == 1 && outPath.at(0).second == 1) &&
        (outPath.at(1).first == 1 && outPath.at(1).second == 2) )
    {
        match = true;
    }
    QVERIFY(match);
}

void PathFinderUT::testExtractPath2()
{
    // Read Puzzle2.txt this time...
    std::vector<std::string> puzzle2;
    std::string curLine;

    std::ifstream inFile ("../../Puzzle2.txt");
    QVERIFY (inFile.is_open());

    while (std::getline (inFile, curLine))
    {
        puzzle2.emplace_back(curLine);
        //std::cout << *(inGrid.end()-1) << "\n";
    }
    inFile.close();


    PathFinder pf(puzzle2);
    std::vector<std::pair<int,int>> outPath = pf.extractPath();
    QVERIFY(outPath.size() == 9);

    // Only 1 possibility here...
    QVERIFY ( (outPath.at(0).first == 2 && outPath.at(0).second == 2) &&
              (outPath.at(1).first == 2 && outPath.at(1).second == 3) &&
              (outPath.at(2).first == 2 && outPath.at(2).second == 4) &&
              (outPath.at(3).first == 2 && outPath.at(3).second == 5) &&
              (outPath.at(4).first == 2 && outPath.at(4).second == 6) &&
              (outPath.at(5).first == 3 && outPath.at(5).second == 6) &&
              (outPath.at(6).first == 3 && outPath.at(6).second == 7) &&
              (outPath.at(7).first == 4 && outPath.at(7).second == 7) &&
              (outPath.at(8).first == 5 && outPath.at(8).second == 7)
            );
}

void PathFinderUT::testExtractPath3()
{
    std::vector<std::string> file;
    file.emplace_back(std::string("X X X"));
    file.emplace_back(std::string("X XAX"));
    file.emplace_back(std::string("X X X"));
    file.emplace_back(std::string("XBX X"));
    file.emplace_back(std::string("X X X"));

    PathFinder pf (file);
    QVERIFY(pf.validateInputFile());

    std::vector<std::pair<int,int>> outPath = pf.extractPath();
    QVERIFY(outPath.size() == 0);   // Target is not reachable...
}
