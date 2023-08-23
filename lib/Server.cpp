#include "Server.h"


//c'tor
ServerProcessor::ServerProcessor(queue<FrameWrap>& queue) :dataFromCamera(queue) {
	active = true;
}

void ServerProcessor::detect_with_YOLO5() {
	cout << "detact func calls: " << currentTime() << endl;

	Yolo5 yolo(currFrame);

	yolo.detect();
	cout << "detact func finish: " << currentTime() << endl;
	cout << "rect start: " << currentTime() << endl;

	RectHandler rect(currFrame, yolo.getOutput(), yolo.getClassList(), sqlHandler);
	rect.toDrawRect();
	cout << "rect start: " << currentTime() << endl;

}

void ServerProcessor::run() {
	cout << "while start: " << currentTime() << endl;

	while (active)
	{
		cout << dataFromCamera.size() << "\n";
		if (!dataFromCamera.empty())
		{
			cout << "in while .front(): " << currentTime() << endl;
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
	cout << "server start: " << currentTime()<<endl;
	server.run();
	Logger::Info("server is runing");
}