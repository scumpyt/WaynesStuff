#ifndef MISCEVENTUT_H
#define MISCEVENTUT_H

#include <QObject>
#include <memory>

class MiscEventUT : public QObject
{
    Q_OBJECT
public:
    MiscEventUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCtor();
    void testCompareOper();
    void testPrintOper();
};

#endif // MISCEVENTUT_H
