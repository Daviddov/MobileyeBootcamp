#include "QueueSafe.h"
using namespace std;

template <typename T>
QueueSafe<T>::QueueSafe() : frontIdx(0), rearIdx(0), to_read(0) {}

template <typename T>
void QueueSafe<T>::push(T& x)
{
	m.lock();
	
	// if old data will overwrite:
	if (to_read > 0 && rearIdx == frontIdx) {
		frontIdx = (frontIdx + 1) % QUEUE_SIZE;
		to_read--;
	}
	arr[rearIdx] = x;
	to_read++;
	rearIdx = (rearIdx + 1) % QUEUE_SIZE; // Fixed the issue here
	
	m.unlock();
}

template <typename T>
T QueueSafe<T>::pop()
{
    m.lock();
    if (to_read < 1) // queue is empty
    {
        m.unlock();
        //cout << "queue is empty" << endl;
        Logger::Info("queue is empty");
        return T();
    }
    T poppedValue = arr[frontIdx];
    frontIdx = (frontIdx + 1) % QUEUE_SIZE;
    to_read--;
    m.unlock();
    return poppedValue;
}

template <typename T>
T QueueSafe<T>::front()
{
    m.lock();
    if (to_read < 1) // queue is empty
    {
        m.unlock();
        //cout << "queue is empty" << endl;
        Logger::Info("queue is empty");
        return T();
    }
    T frontValue = arr[this->frontIdx];

    m.unlock();
    return frontValue;
}

template <typename T>
bool QueueSafe<T>::empty()
{
	return (to_read < 1);
}

template <typename T>
int QueueSafe<T>::size()
{
	return to_read;
}


// Explicitly instantiate for the types you'll use. 
template class QueueSafe<FrameWrap>;

