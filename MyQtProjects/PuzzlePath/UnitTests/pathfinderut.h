#ifndef PATHFINDERUT_H
#define PATHFINDERUT_H

#include <QObject>
#include <vector>
#include <string>

class PathFinderUT : public QObject
{
        Q_OBJECT
public:
    PathFinderUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testBasics1();
    void testBasics2();
    void testFindNode();
    void testGetChar();
    void testSearchNode();
    void testValidateInputFile1();
    void testValidateInputFile2();
    void testExtractPath1();
    void testExtractPath2();
    void testExtractPath3();

private:
    std::vector<std::string> inGrid;
};

#endif // PATHFINDERUT_H
