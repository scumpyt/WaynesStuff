#ifndef OILCHANGEUT_H
#define OILCHANGEUT_H

#include <QObject>
#include <memory>

class OilChangeUT : public QObject
{
    Q_OBJECT
public:
    OilChangeUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testCtor();
    void testCompareOper();
    void testPrintOper();
};

#endif // OILCHANGEUT_H
