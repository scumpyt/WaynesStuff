#ifndef SCHEDULEDMAINTUT_H
#define SCHEDULEDMAINTUT_H

#include <QObject>
#include <memory>

class ScheduledMaintUT : public QObject
{
    Q_OBJECT
public:
    ScheduledMaintUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCtor();
    void testCompareOper();
    void testPrintOper();
};

#endif // SCHEDULEDMAINTUT_H
