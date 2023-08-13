#include "lib/Header.h"

int main() {


	queue<FrameWrap> dataFromCamera;

	FrameWrap frame;

	VideoCapture capture(R"(./assets/parking.mp4)");
	if (!capture.isOpened())
	{
		cerr << "\nError opening video file\n";
		return 1;
	}

	capture.read(frame.image);

	int count_frames = 1;

	frame.frameNamber = count_frames;
	frame.timestamp = currentTime();

	FrameWrap temp;
	temp = frame;
	temp.image = frame.image.clone();
	dataFromCamera.push(temp);


	while (true)
	{
		capture.read(frame.image);


		frame.timestamp = currentTime();

		count_frames++;
		frame.frameNamber = count_frames;
		if (frame.image.empty())
		{
			cout << "End of stream\n";
			break;
		}

		if (frame.frameNamber % 30 == 0 && calcAbsDiff(dataFromCamera.back().image, frame.image))
		{
			temp = frame;
			temp.image = frame.image.clone();
			dataFromCamera.push(temp);
		}
		else {
			continue;
		}

		FrameWrap currFrame = dataFromCamera.front();

		dataFromCamera.pop();

		detect_with_YOLO5(currFrame);

		cv::imshow("output", currFrame.image);

		if (waitKey(1) == 27)
		{
			capture.release();
			cout << "finished by user\n";
			break;
		}
	}
	return 0;
}







