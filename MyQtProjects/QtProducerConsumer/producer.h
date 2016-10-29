#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>

class Producer
{
public:
    explicit Producer();

signals:
    void unitProduced(int); // Templatize to T ???

public slots:
};

#endif // PRODUCER_H
