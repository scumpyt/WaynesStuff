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

private:
    std::vector<std::string> inGrid;
};

#endif // PATHFINDERUT_H
