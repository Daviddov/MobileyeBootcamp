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
	
}

void ServerProcessor::run() {

	while (active)
	{
		if (!dataFromCamera.empty())
		{
			currFrame = dataFromCamera.pop();

			detect_with_YOLO5();

			RectHandler rect(currFrame, yolo.getOutput(), yolo.getClassList(), sqlHandler);
			rect.drawAllDetectsBoxs();

			Size size(800, 600);
			resize(currFrame.image, currFrame.image, size, CV_8UC3),
				cv::imshow("output", currFrame.image);

			if (waitKeyEx(1) == 27)
			{
				Logger::Info("part server finished by user");
				break;
			}
		}
		else {
			Logger::Info("data From Camera empty");
			//cout << "data From Camera empty" << endl;
			waitKeyEx(333);
			//dataFromCamera.waitUntilNotEmpty();
		}
	}
}
