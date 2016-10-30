#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <memory>
#include <iostream>
#include <thread>

#include "worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , myWorker(nullptr)
    , myWorkerThread(nullptr)
{
    QWidget * wdg = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(wdg);
    QPushButton *btn1 = new QPushButton("RUN");
    vlay->addWidget(btn1);
    QPushButton *btn2 = new QPushButton("Do Something Else!");
    vlay->addWidget(btn2);
    QPushButton *btn3 = new QPushButton("QUIT!");
    vlay->addWidget(btn3);
    setCentralWidget(wdg);

    connect (btn1, SIGNAL(pressed()), this, SLOT(onRunPressed()));
    connect (btn2, SIGNAL(pressed()), this, SLOT(onOtherPressed()));
    connect (btn3, SIGNAL(pressed()), this, SLOT(onQuitPressed()));

    std::cout << "Main GUI thread ID = "
              << std::this_thread::get_id() << std::endl;
}

MainWindow::~MainWindow()
{
//    std::cout << "Main DTOR thread ID = "
//              << std::this_thread::get_id() << std::endl;
    myStopWork();
    if (myWorkerThread != nullptr)
    {
        if (myWorkerThread->isRunning())
        {
            // Force the thread to stop.

            // Note: The use of terminate is discouraged because the thread
            //       can be terminated while modifying data, and has no chance
            //       unlock any mutexes, etc. etc., but, as we are exiting out
            //       of the application, it's use here should be harmless.
            //       The only reason I am forcing it here is to get rid of a
            //       message saying "QThread: Destroyed while thread is still running"
            //       when I click on the window 'X' while the thread is running.
            //       This, too, is probably harmless for the same reasons, but
            //       better to not have these funny messages, I guess.
            myWorkerThread->terminate();

            // This will wait for the first of:
            //    - when the thread returns from run()
            //    - when the given timeout (in ms) is elapsed.
            myWorkerThread->wait(1000);
        }
    }
    myCleanUpWorkerThread();
}

void MainWindow::onRunPressed()
{
    //////////////////////////////////////////////////////////////////////////////
    // This is an example of how to take advantage of the fact that the DEFAULT
    // implementation of Qthread::run() actually calls QThread::exec(). This implies
    // AN EVENT LOOP, and allows us to run code in other threads without subclassing
    // QThread:
    // The simple premise is as follows:
    //    1) - When the thread is started, we start the 'doWork' method.
    //    2) - Whenever 'doWork' creates a 'unit' of work, the 'signalUnitProduced'
    //         signal is emitted, presumably being listened for in the main GUI thread.
    //         These signals are queuedConnections, so the main GUI receives them
    //         in the order created.
    //    3) - Calling stopWork simply sets the atomic bool 'myIsRunning' to false
    //         which kicks it out of the 'doWork' loop. It then emits the 'signalWorkDone'
    //         signal, which in turn triggers the thread to quit, and the Worker
    //         object is set to 'deleteLater'
    //
    // NOTES:
    //       -
    //////////////////////////////////////////////////////////////////////////////
    qDebug() << "RUN Pressed";

    // Allocate a new Worker obj.
    // NOTE, that I tried to get this to work as std::shared_ptr instead of a
    //       raw ptr, but I couldn't figure out how to connect the contents of
    //       that with the 'deleteLater' thingy.
    myWorker = new Worker;

    //auto workerThread = new QThread;
    //std::cout << "THREAD TYPE = " << typeid(workerThread).name() << std::endl;

    myCleanUpWorkerThread();
    myWorkerThread = new QThread;

    // Connections...
    connect(myWorkerThread, &QThread::started,        myWorker,         &Worker::doWork);
    connect(myWorker,       &Worker::signalWorkDone,  myWorkerThread,   &QThread::quit);
    connect(myWorkerThread, &QThread::finished,       myWorker,         &Worker::deleteLater);

    connect(myWorker, SIGNAL(signalUnitProduced(int)), this, SLOT(onUnitProduced(int)));

    // Move to thread and start running...
    myWorker->moveToThread(myWorkerThread);
    myWorkerThread->start();
}

void MainWindow::myCleanUpWorkerThread()
{
    if (myWorkerThread != nullptr)
    {
        std::cout << "myCleanUpWorkerThread: DELETING previous thread..." << std::endl;
        delete myWorkerThread;
        myWorkerThread = nullptr;
    }
    else
    {
        std::cout << "myCleanUpWorkerThread: NOT DELETING previous thread..." << std::endl;
    }
}

void MainWindow::onOtherPressed()
{
    qDebug() << "Other Pressed! I'm not blocking!!!";
}

void MainWindow::onQuitPressed()
{
    qDebug() << "QUIT Pressed";
    myStopWork();
}

void MainWindow::myStopWork()
{
    std::cout << "Main myStopWork() called - thread ID = "
              << std::this_thread::get_id() << std::endl;
    // Trigger the end of the doWork loop...
    if (myWorker) myWorker->stopWork();
}

void MainWindow::onUnitProduced(int val)
{
    // Diagnostic printout only...
    if ((val % 10) == 0)
    {
        std::cout << "NEW VAL " << val << " RECEIVED on thread ID: "
                  << std::this_thread::get_id() << std::endl;
    }
}
