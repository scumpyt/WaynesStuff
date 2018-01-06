#ifndef PERSISTENCEENGINEFACTORYUT_H
#define PERSISTENCEENGINEFACTORYUT_H

#include <QObject>

class PersistenceEngineFactoryUT : public QObject
{
    Q_OBJECT
public:
    PersistenceEngineFactoryUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testEngineName();
};

#endif // PERSISTENCEENGINEFACTORYUT_H
