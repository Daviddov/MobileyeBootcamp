#pragma once

#include <mutex>
#include <condition_variable>
#include "FrameWarp.h"
#include "../thirdParty/lib_logger/Logger.h"

#ifndef _SAFE_QUEUE_H_
#define _SAFE_QUEUE_H_


#define QUEUE_SIZE 5

template <typename T>
class QueueSafe
{
private:
	int frontIdx, rearIdx;
	int to_read;
	T arr[QUEUE_SIZE];
	//std::mutex m;
	//std::condition_variable conditionVar;

public:
	QueueSafe();

	void push(T& x);

	T pop();

	T front();

	bool empty();

	int size();

	std::mutex m;

   // void waitUntilNotEmpty();
};


#endif // !_SAFE_QUEUE_H_

