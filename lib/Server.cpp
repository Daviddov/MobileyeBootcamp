#include "Server.h"
#include <chrono>
using namespace std::chrono;
using namespace cv;
//c'tor
ServerProcessor::ServerProcessor(Queue<FrameWrap>& queue) :dataFromCamera(queue) {
	active = true;
	
}

void ServerProcessor::detect_with_YOLO5() {

	yolo.setFrame(currFrame);

	yolo.detect();

	RectHandler rect(currFrame, yolo.getOutput(), yolo.getClassList(), sqlHandler);

	rect.toDrawRect();
	
}

void ServerProcessor::run() {

	while (active)
	{
		if (!dataFromCamera.empty())
		{
			currFrame = dataFromCamera.front();


			//cv::imshow("Server", currFrame.image);
			detect_with_YOLO5();

			Size size(600, 400);

			resize(currFrame.image, currFrame.image, size, CV_8UC3),
				cv::imshow("Server", currFrame.image);

			if (waitKeyEx(1) == 27)
			{
				Logger::Info("part server finished by user");
				break;
			}
		}
		else {
			cout << "TEST" << endl;
			Logger::Info("data From Camera empty");
			waitKeyEx(333);
		}
	}
}
