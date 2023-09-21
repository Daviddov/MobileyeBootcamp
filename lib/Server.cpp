#include "Server.h"


using namespace std::chrono;
using namespace cv;

//c'tor
ServerProcessor::ServerProcessor(QueueSafe<FrameWrap>& queue, condition_variable& condition) :dataFromCamera(queue), conditionVar(condition), countDetects(0) {
	active = true;
}

void ServerProcessor::detect_with_YOLO5() {

	yolo.setFrame(currFrame);

	yolo.detect();

}

void ServerProcessor::run() {

	while (active) {

		if (dataFromCamera.empty()) {
			//cout << "whit..." << endl;
			Logger::Info("whit...");
			waitForData();
			//cout << "continue..." << endl;
			Logger::Info("continue...");
		}
		currFrame = dataFromCamera.pop();

		detect_with_YOLO5();
		countDetects++;
		Logger::Info("counter Detects:", countDetects);
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