#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Worker.h"
//#include <memory>
#include <QThread>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onRunPressed();
    void onOtherPressed();
    void onQuitPressed();

    void onUnitProduced(int value);

private:
    void myStopWork();
    void myCleanUpWorkerThread();

private:
    Worker*     myWorker;
    QThread*    myWorkerThread;
};

#endif // MAINWINDOW_H
