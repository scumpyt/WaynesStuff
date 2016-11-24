#ifndef BYTEQUEUEHELPER_H
#define BYTEQUEUEHELPER_H

#include <mutex>
#include <deque>

#include "cppsrc_global.h"

class CPPSRCSHARED_EXPORT ByteQueueHelper
{
public:
    ByteQueueHelper();
   ~ByteQueueHelper();

    void                        printQueue      () const;        // Test junk only, delete eventually...

    std::mutex&                 getMutex        ();

    void                        qAppend         (std::deque<unsigned char>& theQueue, const std::deque<unsigned char>& readBuffer);
    void                        qAppend         (std::deque<unsigned char>& theQueue, const char* readBuffer, size_t readBufSize);

    void                        qClear          (std::deque<unsigned char>& theQueue);
    void                        qRemove         (std::deque<unsigned char>& theQueue, int start, int count);
    size_t                      qSize           (std::deque<unsigned char>& theQueue);
    bool                        isQueueEmpty    (std::deque<unsigned char>& theQueue);
    std::deque<unsigned char>   qMid            (std::deque<unsigned char>& theQueue, int start, int count);
    unsigned char               qAt             (std::deque<unsigned char>& theQueue, size_t pos);
    int                         qIndexOf        (std::deque<unsigned char>& theQueue, unsigned char c, size_t from = 0);
    int                         qIndexOf        (std::deque<unsigned char>& theQueue,
                                                 const std::deque<unsigned char>& matchBuf, size_t from = 0);

private:
    std::mutex                  myMutex;
};

#endif // BYTEQUEUEHELPER_H
