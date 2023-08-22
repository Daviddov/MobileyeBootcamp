#include "Server.h"

//c'tor
ServerProcessor::ServerProcessor(queue<FrameWrap>& queue) :dataFromCamera(queue) {
	active = true;
}

void ServerProcessor::detect_with_YOLO5() {

	Yolo5 yolo(currFrame);
	yolo.detect();

	RectHandler rect(currFrame, yolo.getOutput(), yolo.getClassList(), sqlHandler);
	rect.toDrawRect();
}

void ServerProcessor::run() {

	while (active)
	{
		cout << dataFromCamera.size() << "\n";
		if (!dataFromCamera.empty())
		{
			currFrame = dataFromCamera.front();

			dataFromCamera.pop();

			detect_with_YOLO5();

			cv::imshow("output", currFrame.image);

			if (waitKey(1) == 27)
			{
				Logger::Info("part server finished by user");
				break;
			}
		}
		else {
			waitKey(1);
		}
	}
}

void ServerProcessor::serverPart(ServerProcessor& server) {
	server.run();
	Logger::Info("server is runing");
}