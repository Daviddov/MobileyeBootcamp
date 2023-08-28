#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <opencv2/opencv.hpp>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;

    // Push an element into the queue
    void Push(const T& value);

    // Pop an element from the queue. If the queue is empty, it will repeatedly check until an element is available.
    T Pop();

    // Check if the queue is empty
    bool Empty() const;

    // Get the size of the queue
    size_t Size() const;

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
};

#endif // THREAD_SAFE_QUEUE_H
