#pragma once
#include "Yolo.h"
#include "RectHandler.h"
#include <chrono>
#include "QueueSafe.h"

class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	QueueSafe<FrameWrap>& dataFromCamera;

	condition_variable& conditionVar;

	SQLHandler sqlHandler;

	Yolo5 yolo;

public:

	ServerProcessor(QueueSafe<FrameWrap>& dataFromCamera, condition_variable& condition);

	void detect_with_YOLO5();

	void run();

	void waitForData();
};
