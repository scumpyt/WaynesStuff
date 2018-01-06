#ifndef PERSISTENCEENGINEUT_H
#define PERSISTENCEENGINEUT_H

#include <QObject>

class PersistenceEngineUT : public QObject
{
    Q_OBJECT
public:
    PersistenceEngineUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testParseVehicles();
    void testParseEvents();
};

#endif // PERSISTENCEENGINEUT_H
