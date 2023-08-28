#include <iostream>

template <typename T>
queueTreadSafe<T>::queueTreadSafe() : front(0), rear(0), to_read(0) {}

// Pushing anyway, even old data will overwrite
template <typename T>
void queueTreadSafe<T>::push(T x)
{
    m.lock();
    // if old data will overwrite:
    if (to_read > 0 && rear == front)  {
        front = (front + 1) % QUEUE_SIZE;
        to_read--;
    }
    arr[rear] = x;  
    to_read++;
    rear = (rear + 1) % QUEUE_SIZE; // Fixed the issue here
    m.unlock();
}

template <typename T>
bool queueTreadSafe<T>::pop(T& x)
{
    m.lock();
    if (to_read < 1) // queue is empty
    {
        m.unlock();
        return false;
    }
    x = arr[front];
    front = (front + 1) % QUEUE_SIZE;
    to_read--;
    m.unlock();
    return true;
}

template <typename T>
bool queueTreadSafe<T>::is_empty()
{
    return (to_read < 1);
}

template <typename T>
int queueTreadSafe<T>::size()
{
    return to_read ;
}

// Explicitly instantiate for the types you'll use. 
template class queueTreadSafe<FrameWrap>;

