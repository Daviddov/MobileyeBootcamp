#pragma once
#include "Yolo.h"
#include "RectHandler.h"


class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	Queue<FrameWrap>& dataFromCamera;

	condition_variable& conditionVar;

	SQLHandler sqlHandler;

	Yolo5 yolo;

public:

	ServerProcessor(Queue<FrameWrap>& dataFromCamera, condition_variable& condition);

	void detect_with_YOLO5();

	void run();

	void waitForData();
};
