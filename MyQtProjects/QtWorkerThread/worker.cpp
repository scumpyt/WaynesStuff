#include "worker.h"
#include <chrono>
#include <mutex>
#include <memory>
#include <thread>
#include <iostream>

Worker::Worker(QObject *parent)
  : QObject(parent)
  , myIsRunning(false)
{

}

Worker::~Worker()
{
    std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
    std::cout << "WORK DTOR Called on thread ID: "
              << std::this_thread::get_id() << std::endl;
}

void Worker::doWork()
{
    std::atomic<int> itr = 0;
    myIsRunning = true;
    while(myIsRunning)
    {
        // Simulate "work" taking some time...
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // Send signal that "work" produced something...
        // (An int, in this case, but could be any object as well)
        signalUnitProduced(++itr);

//        // Push the "produced" value onto the queue...
//        myThreadSafeQueue.push(++itr);

        // Diagnostic printout only...
        if ((itr % 10) == 0)
        {
            std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
            std::cout << "PUSH " << itr << " on thread ID: "
                      << std::this_thread::get_id() << std::endl;
        }

//        // Note. itr should possibly be checked that it doesn't wrap,
//        //       but is not really important here.
    }

    std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
    std::cout << "WORK DONE on thread ID: "
              << std::this_thread::get_id() << std::endl;
    emit signalWorkDone();
}

void Worker::stopWork()
{
    std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
    std::cout << "STOP WORK called on thread ID: "
              << std::this_thread::get_id() << std::endl;

    if (!myIsRunning) return;

    // Trigger doWork to stop it's loop...
    myIsRunning = false;

    //std::unique_lock<std::mutex> lock(myMainMutex);       // Make cout atomic
    std::cout << "STOP WORK DONE on thread ID: "
              << std::this_thread::get_id() << std::endl;
}
