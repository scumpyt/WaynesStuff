#ifndef TIREROTATIONUT_H
#define TIREROTATIONUT_H

#include <QObject>
#include <memory>

class TireRotationUT : public QObject
{
    Q_OBJECT
public:
    TireRotationUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCtor();
    void testCompareOper();
    void testPrintOper();
};

#endif // TIREROTATIONUT_H
