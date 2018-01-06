#ifndef VEHICLEUT_H
#define VEHICLEUT_H

#include <QObject>

class VehicleUT : public QObject
{
    Q_OBJECT
public:
    VehicleUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCtor();
    void testCopyAndAssignment();
    void testPrintOper1();
    void testPrintOper2();
    void testCompareOpers();
};

#endif // VEHICLEUT_H
