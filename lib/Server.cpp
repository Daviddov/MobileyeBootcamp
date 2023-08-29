#include "Server.h"
#include <chrono>
using namespace std::chrono;

//c'tor
ServerProcessor::ServerProcessor(queue<FrameWrap>& queue) :dataFromCamera(queue) {
	active = true;
	
}

void ServerProcessor::detect_with_YOLO5() {

	yolo.setFrame(currFrame);

	yolo.detect();

	//Detect function runtime : 1379 ms
	RectHandler rect(currFrame, yolo.getOutput(), yolo.getClassList(), sqlHandler);

	rect.toDrawRect();
	
}

void ServerProcessor::run() {

	while (active)
	{
		if (!dataFromCamera.empty())
		{
			currFrame = dataFromCamera.front();

			dataFromCamera.pop();

			detect_with_YOLO5();
			Size size(600, 400);
			resize(currFrame.image, currFrame.image, size, CV_8UC3),
				cv::imshow("output", currFrame.image);

			if (waitKeyEx(333) == 27)
			{
				Logger::Info("part server finished by user");
				break;
			}
		}
		else {
			Logger::Info("data From Camera empty");
			waitKeyEx(333);
		}
	}
}

void ServerProcessor::serverPart(ServerProcessor& server) {
	
	server.run();
	Logger::Info("server is runing");
}