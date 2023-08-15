#include "Server.h" 


void serverPart(queue<FrameWrap>& dataFromCamera, bool& isActive) {

	while (isActive)
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
				isActive = false;
				cout << "part server finished by user\n";
				break;
			}
		}
		if (!isActive) break;
	}
}