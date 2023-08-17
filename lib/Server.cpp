#include "Server.h"

ServerProcessor::ServerProcessor(queue<FrameWrap>& queue):dataFromCamera(queue){

	active = true;
}

void ServerProcessor::detect_with_YOLO5(FrameWrap& currFrame) {

	dnn::Net net;

	load_net(net);

	vector<string> class_list = load_class_list();

	vector<Detection> output;

	detect(currFrame.image, net, output, class_list);

	toDrawRect(currFrame, output, class_list);
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