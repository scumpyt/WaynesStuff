#include "bytequeuehelper.h"
#include <iostream>
#include <algorithm>
#include <iterator>


ByteQueueHelper::ByteQueueHelper()
{

}

ByteQueueHelper::~ByteQueueHelper()
{

}

void ByteQueueHelper::printQueue() const
{
    std::cout << "printQueue called..." << std::endl;
}

std::mutex& ByteQueueHelper::getMutex()
{
    return myMutex;
}

void ByteQueueHelper::qAppend(std::deque<unsigned char>& theQueue, const std::deque<unsigned char>& fromBuffer)
{
    std::unique_lock<std::mutex> lock(myMutex);
    theQueue.insert(theQueue.end(), fromBuffer.begin(), fromBuffer.end());
}

void ByteQueueHelper::qAppend(std::deque<unsigned char>& theQueue, const char* readBuffer, size_t readBufSize)
{
    std::unique_lock<std::mutex> lock(myMutex);
    for (auto i=0; i<readBufSize; ++i)
    {
        theQueue.emplace_back((unsigned char)readBuffer[i]);     // Probably a more efiicient way to do this ???
    }
}


void ByteQueueHelper::qClear(std::deque<unsigned char>& theQueue)
{
    std::unique_lock<std::mutex> lock(myMutex);
    theQueue.clear();
}

void ByteQueueHelper::qRemove(std::deque<unsigned char>& theQueue, int start, int count)
{
    std::unique_lock<std::mutex> lock(myMutex);

    auto startItr = max(theQueue.begin(), theQueue.begin()+start);
    auto endItr   = min((startItr + count), theQueue.end());

    theQueue.erase(startItr, endItr);
}

size_t ByteQueueHelper::qSize(std::deque<unsigned char>& theQueue)
{
    std::unique_lock<std::mutex> lock(myMutex);
    return theQueue.size();
}


bool ByteQueueHelper::isQueueEmpty(std::deque<unsigned char>& theQueue)
{
    std::unique_lock<std::mutex> lock(myMutex);
    return theQueue.empty();
}

std::deque<unsigned char> ByteQueueHelper::qMid(std::deque<unsigned char>& theQueue, int start, int count)
{
    std::unique_lock<std::mutex> lock(myMutex);

    auto startItr = max(theQueue.begin(), theQueue.begin()+start);
    auto endItr   = min((startItr + count), theQueue.end());

    std::deque<unsigned char> outQueue;

    std::copy(startItr, endItr, std::back_inserter(outQueue));
    return outQueue;
}

unsigned char ByteQueueHelper::qAt(std::deque<unsigned char>& theQueue, size_t pos)
{
    std::unique_lock<std::mutex> lock(myMutex);
    return theQueue.at(pos);    // NOTE will throw if pos out of range...
}

int ByteQueueHelper::qIndexOf (std::deque<unsigned char>& theQueue, unsigned char c, size_t from)
{
    std::unique_lock<std::mutex> lock(myMutex);
    int indx = -1;

    auto startItr  = min(max(theQueue.begin(), theQueue.begin()+from), theQueue.end());
    auto resultItr = std::find_if(startItr, theQueue.end(), [=](unsigned char qc) { return qc==c; });

    if (resultItr != theQueue.end()) indx = (resultItr - startItr);

    return indx;
}

int ByteQueueHelper::qIndexOf(std::deque<unsigned char>& theQueue,
                              const std::deque<unsigned char>& matchBuf, size_t from)
{
    std::unique_lock<std::mutex> lock(myMutex);
    int indx = -1;

    auto startItr  = min(max(theQueue.begin(), theQueue.begin()+from), theQueue.end());
    auto resultItr = std::search(startItr, theQueue.end(), matchBuf.begin(), matchBuf.end());

    if (resultItr != theQueue.end()) indx = (resultItr - startItr);

    return indx;
}
