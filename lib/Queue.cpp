#include "Queue.h"

template <typename T>
Queue<T>::Queue() : frontIdx(0), rearIdx(0), to_read(0) {}

// Pushing anyway, even old data will overwrite



template <typename T>
void Queue<T>::push(T& x)
{
    m.lock();
    // if old data will overwrite:
    if (to_read > 0 && rearIdx == frontIdx)  {
        frontIdx = (frontIdx + 1) % QUEUE_SIZE;
        to_read--;
    }
    arr[rearIdx] = x;  
    to_read++;
    rearIdx = (rearIdx + 1) % QUEUE_SIZE; // Fixed the issue here
    m.unlock();
}
template <typename T>
T Queue<T>::pop()
{
    m.lock();
    if (to_read < 1) // queue is empty
    {
        m.unlock();
        cout << "queue is empty" << endl;
        return T();
    }
    T x = arr[frontIdx];
    frontIdx = (frontIdx + 1) % QUEUE_SIZE;
    to_read--;
    m.unlock();
    return x;
}

template <typename T>
T Queue<T>::front()
{
    m.lock();
    if (to_read < 1) // queue is empty
    {
        m.unlock();
        cout << "queue is empty" << endl;
        return T();
    }
    T x = arr[this->frontIdx];
    frontIdx = (frontIdx + 1) % QUEUE_SIZE;
    to_read--;
    m.unlock();
    return x;
}



template <typename T>
bool Queue<T>::empty()
{
    return (to_read < 1);
}

template <typename T>
int Queue<T>::size()
{
    return to_read ;
}

// Explicitly instantiate for the types you'll use. 
template class Queue<FrameWrap>;

