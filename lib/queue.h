#pragma once
#include "Header.h"
#include <mutex>
#include <condition_variable>

#ifndef _SAFE_QUEUE_H_
#define _SAFE_QUEUE_H_


#define QUEUE_SIZE 5

template <typename T>
class Queue
{
private:
	int frontIdx, rearIdx;
	int to_read;
	T arr[QUEUE_SIZE];
	//std::mutex m;
	//std::condition_variable conditionVar;

public:
	Queue();

	void push(T& x);

	T pop();

	T front();

	bool empty();

	int size();

	std::mutex m;

   // void waitUntilNotEmpty();
};


#endif // !_SAFE_QUEUE_H_

