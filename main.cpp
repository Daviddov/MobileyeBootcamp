#include "lib/Header.h"

//something instead waitKey for exit from while(true) in camera part.
//mutex!!!!!!!!!!!!

void cameraPart(queue<FrameWrap>&dataFromCamera) {

	FrameWrap frame;

	//VideoCapture capture(R"(./assets/parking.mp4)");
	VideoCapture capture(R"(C:\Users\1\Desktop\project_files\police.mp4)");
	//VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cerr << "\nError opening video file\n";
		return;
	}

	capture.read(frame.image);

	int count_frames = 1;

	frame.frameNamber = count_frames;
	frame.timestamp = currentTime();

	dataFromCamera.push(frame); 

	Mat prev = frame.image;

	while (true)
	{
		FrameWrap frame;

		capture.read(frame.image);

		frame.timestamp = currentTime();

		frame.frameNamber = ++count_frames;

		if (frame.image.empty())
		{
			cout << "End of stream\n";
			break;
		}

		if (frame.frameNamber % 30 == 0 && calcAbsDiff(prev, frame.image))
		{
			prev = frame.image;
			dataFromCamera.push(frame);
			cout << "pushing!!!!!!!!!!!" << endl;
		}
		else {
			//cout << "rejected!!!!!!!!!!!" << endl;
			continue;
		}

		if (waitKey(1) == 27)
		{
			capture.release();
			cout << "part camera finished by user\n";
			break;
		}
		cout << "part camera\n";
	}
}

void serverPart(queue<FrameWrap>&dataFromCamera) {

	while (true)
	{
		cout << dataFromCamera.size()<< "\n";
		if (!dataFromCamera.empty())
		{
			FrameWrap currFrame = dataFromCamera.front();

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

int main() {

	queue<FrameWrap> dataFromCamera;

	thread cameraThread(cameraPart, ref(dataFromCamera));

	thread serverThread(serverPart, ref(dataFromCamera));

	cameraThread.join();
	serverThread.join();
	
	return 0;
}

