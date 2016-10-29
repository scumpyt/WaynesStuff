#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "threadmanager.h"

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

private:
    //ThreadManager *myManager;
};

#endif // MAINWINDOW_H
