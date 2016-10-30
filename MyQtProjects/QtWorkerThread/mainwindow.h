#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Worker.h"
#include <memory>

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

private:
    std::shared_ptr<Worker> myWorker;   // Should/could this be a unique_ptr???
};

#endif // MAINWINDOW_H
