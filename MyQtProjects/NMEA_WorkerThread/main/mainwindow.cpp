#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include <iostream>

#include "nmeathreadmanager.h"

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

    myManager = new NMEAThreadManager(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onRunPressed()
{
    qDebug() << "RUN Pressed";
    myManager->run();
}

void MainWindow::onOtherPressed()
{
    //qDebug() << "Other Pressed";
    std::cout << "Other Pressed (not blocking!!) on thread ID: "
              << std::this_thread::get_id() << std::endl;
}

void MainWindow::onQuitPressed()
{
    qDebug() << "QUIT Pressed";
    myManager->stop();
}
