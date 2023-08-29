#pragma once
#include "Queue.cpp"

#ifndef _SAFE_QUEUE_H_
#define _SAFE_QUEUE_H_

#include <mutex>

#define QUEUE_SIZE 5

template <typename T>
class queueTreadSafe
{
private:
    int front, rear;
    int to_read;
    T arr[QUEUE_SIZE];
    std::mutex m;

public:
    queueTreadSafe();

    void push(T x);

    bool pop(T& x);

    bool is_empty();

    int size();
};


#endif // !_SAFE_QUEUE_H_

