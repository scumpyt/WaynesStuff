#include "threadmanager.h"
#include <iostream>
#include <chrono>

ThreadManager::ThreadManager(QObject *parent)
    : QObject(parent)
    , myIsRunning(false)
{

}

ThreadManager::~ThreadManager()
{
    std::cout << "ThreadManager dtor called...";
    stop();
}

void ThreadManager::theProducer ()
{
    std::atomic<int> itr = 0;
    while(myIsRunning)
    {
        // Simulate this taking some time...
        // NOTE - playing with the times in both consumer and producer,
        //        can show you how everything runs when one takes
        //        longer than the other.
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // Push the "produced" value onto the queue...
        myThreadSafeQueue.push(++itr);

        // Diagnostic printout only...
        if ((itr % 10) == 0)
        {
            std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
            std::cout << "PUSH " << itr << " on thread ID: "
                      << std::this_thread::get_id() << std::endl;
        }

        // Note. itr should possibly be checked that it doesn't wrap,
        //       but is not really important here.
    }
}

void ThreadManager::theConsumer ()
{
    // NOTE - If the consumer takes a lot longer than the producer,
    //        continuing the loop till empty here (after calling stop())
    //        might take a long time. In that case, we might remove
    //        the check for empty(), here.
    while(myIsRunning || !myThreadSafeQueue.empty())
    {
        int val;

        // Wait on new values, and 'pop' when available...
        myThreadSafeQueue.waitAndPop(val);

        // If T was a large object, this should be used instead of the above...
        // std::shared_ptr<T> ptr = waitAndPop();

        // Here, we would 'do something' with the new values...

        // Simulate this taking some time...
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // Diagnostic printout only...
        if ((val % 10) == 0)
        {
            std::unique_lock<std::mutex> lock(myMainMutex);
            std::cout << "POP " << val << " on thread ID: "
                      << std::this_thread::get_id() << std::endl;
        }
    }
}

void ThreadManager::run()
{
    if (myIsRunning) return;

    std::cout << "Running...";
    std::cout << "... on thread ID: "
              << std::this_thread::get_id() << std::endl;

    myIsRunning = true;

    // Create and start the 2 theads...
    myProducerThread.reset(new std::thread(&ThreadManager::theProducer, this));
    myConsumerThread.reset(new std::thread(&ThreadManager::theConsumer, this));
}

void ThreadManager::stop()
{
    if (!myIsRunning) return;

    // Trigger the threads to stop their loops...
    myIsRunning = false;

    // Wait for the producer to finish up first...
    if (myProducerThread && myProducerThread->joinable())
    {
        myProducerThread->join();
    }

    // Then wait for the consumer to finish up...
    if (myConsumerThread && myConsumerThread->joinable())
    {
        myConsumerThread->join();
    }
}
