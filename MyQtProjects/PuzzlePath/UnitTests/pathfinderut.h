#ifndef PATHFINDERUT_H
#define PATHFINDERUT_H

#include <QObject>

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

    void testBuildEdgeGraph();
};

#endif // PATHFINDERUT_H
