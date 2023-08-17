#include "Server.h"
#include "Yolo.h"
#include "Rect.h"

ServerProcessor::ServerProcessor(queue<FrameWrap>& queue) :dataFromCamera(queue) {

	active = true;
}

void ServerProcessor::detect_with_YOLO5(FrameWrap& currFrame) {

	Yolo5 yolo(currFrame);
	yolo.detect();

	YoloRect rect(currFrame, yolo.getOutput(), yolo.getClassList());
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

			detect_with_YOLO5(currFrame);

			cv::imshow("output", currFrame.image);

			if (waitKey(1) == 27)
			{
				cout << "part server finished by user\n";
				break;
			}
		}

	}
}

void serverPart(ServerProcessor& server) {
	server.run();
}