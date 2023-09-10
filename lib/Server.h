#pragma once
#include "Yolo.h"
#include "RectHandler.h"


class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	Queue<FrameWrap>& dataFromCamera;

	SQLHandler sqlHandler;

	Yolo5 yolo;

public:

	ServerProcessor(Queue<FrameWrap>& dataFromCamera);

	void detect_with_YOLO5(Yolo5 yolo);

	void run();
};
