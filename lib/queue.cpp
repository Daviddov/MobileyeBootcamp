#include "queue.h"

template <typename T>
void ThreadSafeQueue<T>::Push(const T& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
}

template <typename T>
T ThreadSafeQueue<T>::Pop() {
    while (true) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!queue_.empty()) {
            T value = queue_.front();
            queue_.pop();
            return value;
        }
    }
}

template <typename T>
bool ThreadSafeQueue<T>::Empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

template <typename T>
size_t ThreadSafeQueue<T>::Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

// Explicit instantiation for cv::Mat
template class ThreadSafeQueue<cv::Mat>;
