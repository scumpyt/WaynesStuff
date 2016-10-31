#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

///////////////////////////////////////////////////////////////////
/// \brief The ThreadSafeQueue class
/// This is taken almost directly out the "Concurrency in Action"
/// book, page 74. Basically, the coordination between the 'push'
/// and the 'waitAndPop' is done using condition_variables.
/// ///////////////////////////////////////////////////////////////

template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
    {}

    ThreadSafeQueue(ThreadSafeQueue const& rhs)
    {
        std::lock_guard<std::mutex> lock(myMutex);
        myQueue = rhs.myQueue;
    }

    void push(T newValue)
    {
        std::lock_guard<std::mutex> lock(myMutex);
        myQueue.push(newValue);
        myCondVar.notify_one();
    }

    void waitAndPop(T& value)
    {
        std::unique_lock<std::mutex> lock(myMutex);
        myCondVar.wait(lock, [this]{return !myQueue.empty(); });
        value = myQueue.front();
        myQueue.pop();
    }

    std::shared_ptr<T> waitAndPop()
    {
        std::unique_lock<std::mutex> lock(myMutex);
        myCondVar.wait(lock, [this]{return !myQueue.empty(); });
        std::shared_ptr<T> sharedPtrToT (std::make_shared<T>(myQueue.front()));
        myQueue.pop();
        return sharedPtrToT;
    }

    bool tryPop(T& value)
    {
        std::lock_guard<std::mutex> lock(myMutex);
        if (myQueue.empty())
            return false;
        value = myQueue.front();
        myQueue.pop();
        return true;
    }

    std::shared_ptr<T> tryPop()
    {
        std::lock_guard<std::mutex> lock(myMutex);
        if (myQueue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> sharedPtrToT (std::make_shared<T>(myQueue.front()));
        myQueue.pop();
        return sharedPtrToT;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(myMutex);
        return myQueue.empty();
    }

private:
    mutable std::mutex      myMutex;
    std::queue<T>           myQueue;
    std::condition_variable myCondVar;
};


#endif // THREADSAFEQUEUE_H
