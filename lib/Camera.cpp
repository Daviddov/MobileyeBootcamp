#include "Camera.h" 


//c'tor
CameraProcessor::CameraProcessor(Queue<FrameWrap>& queue, int id, string _path) :
	dataFromCamera(queue) ,cameraId (id) ,path  (_path) {
	countFrame = 1;
	active = true;
	cameraId = id;
	path = _path;
	numFramesCheck = 0;
	frameDiffThreshold = 0.0;
}

//d'tor
CameraProcessor::~CameraProcessor() {
	capture.release();
}

bool CameraProcessor::calcAbsDiff() {
	Mat diff;
	absdiff(prev, frameWarp.image, diff);

	//convert diff to gray because countNonZero func can't to resive COLOR_IMG 
	cvtColor(diff, diff, COLOR_BGR2GRAY);
	double normalRes = (double)(countNonZero(diff)) / (double)(frameWarp.image.cols * frameWarp.image.rows);

	return frameDiffThreshold < normalRes;
}

bool CameraProcessor::init(int numFrames, double frameDiff) {
	
	//connect.server_address = "localhost:50051";
	//connect.stub = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
	

	numFramesCheck = numFrames;

	frameDiffThreshold = frameDiff;

	capture.open(path);

	if (!capture.isOpened()) {
		Logger::Error("Error opening video file");
		return false;
	}
	Logger::Info("Video file is opening ");
	capture.read(frameWarp.image);
	insertToQueue();
	return true;
}

//   CameraProcessor::send()
void CameraProcessor::insertToQueue() {

	//1?
	///*vector<uchar> image_data;
	//imencode(".jpg", frameWarp.image, image_data);
	//request.set_image(image_data.data(), image_data.size());*/

	//2?
	//vector<uint8_t> imageBytes(frameWarp.image.data, frameWarp.image.data + frameWarp.image.total() * frameWarp.image.elemSize());
	// Create a CameraDataRequest
	//request.set_image(imageBytes.data(), imageBytes.size());

	//3?
	//request.set_image(frameWarp.image.data, frameWarp.image.total() * frameWarp.image.elemSize());
	
	
	//request.set_timestamp(frameWarp.timestamp);
	//request.set_framenumber(frameWarp.frameNumber);


	// status = stub.SendCameraData(&context, request, &response);

	//if (status.ok()) {
	//	cout << "Server response: " << response.acknowledgment() << endl;
	//}
	//else {
	//	cerr << "RPC failed: " << status.error_message() << endl;
	//}

	//From here //////////////////////////////
	frameWarp.frameNumber = countFrame;     //
	frameWarp.timestamp = currentTime();    //
	FrameWrap temp = frameWarp;             //
	temp.image = frameWarp.image.clone();   //
	dataFromCamera.push(temp);              //
	prev = frameWarp.image.clone();         //
//until here is a temporary until fixed grpc//

}

void CameraProcessor::run() {

	while (active) {

		capture.read(frameWarp.image);
		

		if (frameWarp.image.empty()) {
			cout << "End of stream\n";
			Logger::Info("End of stream");
			break;
		}
		if (++countFrame % numFramesCheck == 0 && calcAbsDiff()) {
			Logger::Info("wait 0.3 second");
			this_thread::sleep_for(chrono::milliseconds(333));
			insertToQueue();
			Logger::Info("insert to queue");
			//From here ///////////////////////////////////
			Mat view = dataFromCamera.front().image;     //      
			imshow("clientMain", view);                  //
			if (waitKey(1) == 27) {                      //
				break;                                   //
			}                                            //
			///until here is a temporary until fixed grpc//

		}
	}
}

std::string currentTime() {
	auto now = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch()
	);

	auto milliseconds = timestamp % 1000;

	auto time_t_timestamp = std::chrono::duration_cast<std::chrono::seconds>(
		timestamp
	).count();

	std::time_t time_t_timestamp_t = static_cast<std::time_t>(time_t_timestamp);

	std::tm timeinfo;
	// Use localtime or gmtime depending on your requirement
#ifdef _WIN32
	localtime_s(&timeinfo, &time_t_timestamp_t);
#else
	localtime_r(&time_t_timestamp_t, &timeinfo);
#endif

	char buffer[28];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

	std::ostringstream formatted_time;
	formatted_time << buffer << ":" << std::setfill('0') << std::setw(3) << milliseconds.count();

	std::cout << "The time is " << formatted_time.str() << std::endl;  // Replace with your logging mechanism
	return formatted_time.str();
}

void CameraProcessor::cameraPart(CameraProcessor* camera) {


	//the user input it using Qt
	int numFrames = 30;

	//the user input it using Qt
	double frameDiffThreshold = 0.9;

	if (!camera->init(numFrames, frameDiffThreshold))
	{
		Logger::Critical("the path is not found");
		return;
	}

	camera->run();

	delete camera;
}

int CameraProcessor::getId() {
	return cameraId;
}