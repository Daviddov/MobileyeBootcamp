#pragma once
#include "Yolo.h"
#include "Rect.h"


class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	queue<FrameWrap>& dataFromCamera;

	SQLHandler sqlHandler;

	Yolo5 yolo;

public:

	ServerProcessor(queue<FrameWrap>& dataFromCamera);

	void detect_with_YOLO5();

	void run();

  static void  serverPart(ServerProcessor& server);
};
