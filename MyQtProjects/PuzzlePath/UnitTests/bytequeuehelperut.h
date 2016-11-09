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
};

#endif // BYTEQUEUEHELPERUT_H
