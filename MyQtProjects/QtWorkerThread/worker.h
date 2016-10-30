#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <atomic>
//#include "threadsafequeue.h"
#include <mutex>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    ~Worker();

signals:
    void signalWorkDone();
    void signalUnitProduced(int value);

public slots:
    void doWork();
    void stopWork();

private:
    std::atomic<bool>       myIsRunning = false;
    //ThreadSafeQueue<int>    myThreadSafeQueue;
    std::mutex                      myMainMutex;
};

#endif // WORKER_H
