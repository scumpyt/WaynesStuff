#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <mutex>
#include <thread>
#include <memory>

#include <future>
#include <atomic>
#include <mutex>

#include "ThreadSafeQueue.h"

///////////////////////////////////////////////////////////////////
/// \brief The ThreadManager class
/// This is the first working version of a simple producer-consumer
/// that I got to work reasonably well. Here's how it works:
/// When "run()" is called, 2 new threads are created (thus
/// destructing any old ones), one for the producer, and one for
/// the consumer. These both continue to run until stop is triggered.
/// "stop()" then calls "join()" on both, to ensure we wait for
/// any unfinished work to complete. (Producer.join() is called
/// first).
///
/// For this simple test, we simply increment an int in the producer.
/// In a real example, the data to be 'produced' would most assuredly
/// be much more complex.
///
/// The data is pushed/popped onto the ThreadSafeQueue. This is
/// an implementation taaken almost word-for-word from the
/// "Concurrency in Action" book, pg. 74. Instead of simple ints
/// (as in this example), actual data could be a complex object.
/// Whether to use smart ptrs and move semantics on this object
/// is unknown at this point, but I'll guess yes.
///
/// NOTE - Altering the amount of time taken in the chrono methods
/// in either the producer or consumer is a great way to show what
/// happenes if one takes longer than the other. This is an excellent,
/// and recommended way of testing basic thread logic.
///
/// Further questions:
/// - It might be a better idea to force the dtor of the threads
///   right after we're finished with them in the 'stop()' method.
/// - Where we create the 2 threads in the 'run()' method, it might
///   be more exception proof to create the threads as one step,
///   and then pass them into the reset as a second.
/// - The actual need for a consumer thread is optional. If you
///   simply need to take the 'produced' data and do something
///   simple with it, this could be replaced with logic directly
///   int the main GUI thread.
/// - If the consumer takes longer than the producer, the queue
///   will have a (potentially large) backlog, when we get to the
///   'stop()' method. You will have to decide whether it makes
///   sense to wait there, or, simply stop processing and ignore
///   the backlog. (For incoming GPS locations, for example, these
///   could easily just be ignored)
/// - Note that this set-up is likely only applicable to the SPSC
///   (Single Producer Single Consumer) situation.
///////////////////////////////////////////////////////////////////

class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = 0);
   ~ThreadManager();

    void theProducer();
    void theConsumer();

public slots:
    void run();
    void stop();

private:
    std::unique_ptr<std::thread>    myProducerThread;
    std::unique_ptr<std::thread>    myConsumerThread;

    ThreadSafeQueue<int>            myThreadSafeQueue;
    std::atomic<bool>               myIsRunning = false;
    std::mutex                      myMainMutex;
};

#endif // THREADMANAGER_H
