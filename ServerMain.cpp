
#include "Header.h"
#include "CameraManager.h"
#include "Server.h"
#include "ConfigurationManager.h"

void tastInsertToQueue(Queue<FrameWrap>& dataFromCamera) {
	FrameWrap werpframe;
	Mat image(500, 500, CV_8UC3, Scalar(111, 22, 33));

	werpframe.image = image.clone(); // Clone the image if necessary
	werpframe.timestamp = currentTime();
	werpframe.frameNumber = 1;

	dataFromCamera.push(werpframe);

	// If the cloned image is no longer needed, release its memory
	werpframe.image.release();
}

int main() {
	 //configRun(); //config json example

	//log init
	LogPriority priority = InfoPriority;
	mutex log_mutex;
	Logger::EnableFileOutput();
	Logger::Info("the programe is started");

	Queue<FrameWrap> dataFromCamera;

	tastInsertToQueue(dataFromCamera);

	ServerProcessor server(dataFromCamera);

	thread serverThread(ServerProcessor::serverPart, ref(server));

	serverThread.join();

	Logger::Info("the programme is finised");

	return 0;
}