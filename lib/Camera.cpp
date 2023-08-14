#include "Camera.h" 


void cameraPart(queue<FrameWrap>& dataFromCamera) {

	FrameWrap frame;

	VideoCapture capture(R"(./assets/parking.mp4)");
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
