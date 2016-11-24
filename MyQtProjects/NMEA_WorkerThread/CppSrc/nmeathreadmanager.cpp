#include "nmeathreadmanager.h"
#include <iostream>
#include <chrono>

NMEAThreadManager::NMEAThreadManager(QObject *parent)
    : QObject(parent)
    , myIsRunning(false)
    , myVal(0)
{
    std::cout << "NMEAThreadManager ctor called..." << std::endl;
}

NMEAThreadManager::~NMEAThreadManager()
{
    std::cout << "NMEAThreadManager dtor called..." << std::endl;
    stop();
}

void NMEAThreadManager::theProducer ()
{
////////////////////////////////// ORIG, working loop ////////////////////////////////
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
//        {
//            std::unique_lock<std::mutex> lock(myMainMutex);
//            if (itr <= 100)
//            {
//                ++itr;          // Only 'produce' till we get to 100
//                myThreadSafeQueue.push(itr);
//            }
//        }

        // Diagnostic printout only...
        if ((itr % 10) == 0)
        {
            std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
            std::cout << "CUR ITR = " << itr << " on thread ID: "
                      << std::this_thread::get_id() << std::endl;
        }

        // Note. itr should possibly be checked that it doesn't wrap,
        //       but is not really important here.
    }
//////////////////////////////////////////////////////////////////////////////////////
}

void NMEAThreadManager::theConsumer ()
{
    // NOTE - If the consumer takes a lot longer than the producer,
    //        continuing the loop till empty here (after calling stop())
    //        might take a long time. In that case, we might remove
    //        the check for empty(), here.
    while(myIsRunning || !myThreadSafeQueue.empty())
    {
        //int val;

        // Wait on new values, and 'pop' when available...
        myThreadSafeQueue.waitAndPop(myVal);    // NOTE - this will BLOCK the Consumer thread, if no data in queue!!!

        // Simulate this taking some time...
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // Diagnostic printout only...
        if ((myVal % 10) == 0)
        {
            std::unique_lock<std::mutex> lock(myMainMutex);
            std::cout << "CUR VAL = " << myVal << " on thread ID: "
                      << std::this_thread::get_id() << std::endl;
        }
    }
}

void NMEAThreadManager::run()
{
    if (myIsRunning) return;

    myVal = 0;  // initialize...

    std::cout << "Running...";
    std::cout << "... on thread ID: "
              << std::this_thread::get_id() << std::endl;

    myIsRunning = true;

    // Create and start the Producer thread...
    myProducerThread.reset(new std::thread(&NMEAThreadManager::theProducer, this));
    myConsumerThread.reset(new std::thread(&NMEAThreadManager::theConsumer, this));

}

void NMEAThreadManager::stop()
{
    if (!myIsRunning) return;

    // Trigger the threads to stop their loops...
    myIsRunning = false;

    // Wait for the producer to finish up first...
    if (myProducerThread && myProducerThread->joinable())
    {
        std::cout << "JOINING Producer on thread "
                  << std::this_thread::get_id() << std::endl;
        myProducerThread->join();
    }
    else
    {
        std::cout << "Producer NOT Joinable on thread "
                  << std::this_thread::get_id() << std::endl;
    }

    // Then wait for the consumer to finish up...
    if (myConsumerThread && myConsumerThread->joinable())
    {
        std::cout << "JOINING Consumer on thread "
                  << std::this_thread::get_id() << std::endl;
        myConsumerThread->join();
    }
    else
    {
        std::cout << "COnsumer NOT Joinable on thread "
                  << std::this_thread::get_id() << std::endl;
    }
}
