#include <QCoreApplication>
#include <iostream>

#include "bytequeuehelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello World!" << std::endl;

    ByteQueueHelper bqh;
    bqh.printQueue();

    return a.exec();
}
