#include "Server.h"
#include <chrono>
using namespace std::chrono;
using namespace cv;
//c'tor
ServerProcessor::ServerProcessor(Queue<FrameWrap>& queue, condition_variable& condition) :dataFromCamera(queue), conditionVar(condition) {
	active = true;
}

void ServerProcessor::detect_with_YOLO5() {

	yolo.setFrame(currFrame);

	yolo.detect();

}

void ServerProcessor::run() {

	while (active) {

		if (dataFromCamera.empty()) {
			cout << "whit..." << endl;
			waitForData();
			cout << "continue..." << endl;
		}
		currFrame = dataFromCamera.pop();

		detect_with_YOLO5();

		RectHandler rect(currFrame, yolo.getOutput(), yolo.getClassList(), sqlHandler);
		rect.drawAllDetectsBoxs();

		Size size(800, 600);
		resize(currFrame.image, currFrame.image, size, CV_8UC3),
			cv::imshow("output", currFrame.image);

		if (waitKeyEx(1) == 27) {

			Logger::Info("part server finished by user");
			break;
		}

	}
}



void ServerProcessor::waitForData() {

	unique_lock<mutex> lock(dataFromCamera.m);

	conditionVar.wait(lock, [this]() {
		return !dataFromCamera.empty();
		});
}