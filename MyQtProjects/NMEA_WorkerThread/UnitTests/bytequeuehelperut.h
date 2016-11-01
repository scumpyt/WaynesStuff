#ifndef BYTEQUEUEHELPERUT_H
#define BYTEQUEUEHELPERUT_H

#include <QObject>

class ByteQueueHelperUT : public QObject
{
    Q_OBJECT
public:
    ByteQueueHelperUT();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void testPrintQueue();
    void testQAppend();
    void testQClear();
    void testQRemove();
    void testQSize();
    void testIsQueueEmpty();
    void testQMid();
    void testQAt();
    void testQIndexOf();
    void testQIndexOf_2();
};

#endif // BYTEQUEUEHELPERUT_H
