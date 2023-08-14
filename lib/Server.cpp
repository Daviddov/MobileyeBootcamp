#include "Server.h" 


void serverPart(queue<FrameWrap>& dataFromCamera) {
	bool active = true;

	while (active)
	{
		cout << dataFromCamera.size() << "\n";
		if (!dataFromCamera.empty())
		{
			FrameWrap currFrame = dataFromCamera.front();

			dataFromCamera.pop();

			detect_with_YOLO5(currFrame);

			cv::imshow("output", currFrame.image);

			if (waitKey(1) == 27)
			{
				active = false;
				cout << "part server finished by user\n";
				break;
			}
		}
	}
}