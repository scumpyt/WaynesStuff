#ifndef NMEATHREADMANAGER_H
#define NMEATHREADMANAGER_H

#include <QObject>
#include <mutex>
#include <thread>
#include <memory>

#include <future>
#include <atomic>
#include <mutex>

#include "ThreadSafeQueue.h"

#include "cppsrc_global.h"

class CPPSRCSHARED_EXPORT NMEAThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit NMEAThreadManager(QObject *parent = 0);
    ~NMEAThreadManager();

     void theProducer();
     void theConsumer();

//public slots:
     void run();
     void stop();

private:
     std::unique_ptr<std::thread>    myProducerThread;
     std::unique_ptr<std::thread>    myConsumerThread;

     ThreadSafeQueue<int>            myThreadSafeQueue;
     std::atomic<bool>               myIsRunning = false;
     std::mutex                      myMainMutex;

     int                             myVal;
};

#endif // NMEATHREADMANAGER_H
