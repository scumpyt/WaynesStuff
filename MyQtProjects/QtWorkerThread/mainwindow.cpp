#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QThread>
#include <memory>
#include <iostream>
#include <thread>

#include "worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    myStopWork();
}

void MainWindow::onRunPressed()
{
    //////////////////////////////////////////////////////////////////////////////
    // This is an example of how to take advantage of the fact that the DEFAULT
    // implementation of Qthread::run() actually calls QThread::exec(). This implies
    // AN EVENT LOOP, and allows us to run code in other threads without subclassing
    // QThread:
    //////////////////////////////////////////////////////////////////////////////
    qDebug() << "RUN Pressed";

    //if (myWorker) myWorker = nullptr;           // Force delete on any existing...
    myWorker = (std::make_shared<Worker>());    // Create new...

    auto workerThread = new QThread;

    // Connections...
    connect(workerThread, &QThread::started,        &(*myWorker),   &Worker::doWork);
    connect(&(*myWorker), &Worker::signalWorkDone,  workerThread,   &QThread::quit);
    connect(workerThread, &QThread::finished,       &(*myWorker),   &Worker::deleteLater);

    connect(&(*myWorker), SIGNAL(signalUnitProduced(int)), this, SLOT(onUnitProduced(int)));

    myWorker->moveToThread(workerThread);
    workerThread->start();
}

void MainWindow::onOtherPressed()
{
    qDebug() << "Other Pressed! I'm not blocking!!!";
}

void MainWindow::onQuitPressed()
{
    qDebug() << "QUIT Pressed";
    myStopWork();
    QString msg = myWorker.get() == nullptr ? "WORKER IS NULL" : "WORKER is NOT NULL";
    qDebug() << msg;
    qDebug() << "QUIT Pressed - AFTER STOP WORK";
}

void MainWindow::myStopWork()
{
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
