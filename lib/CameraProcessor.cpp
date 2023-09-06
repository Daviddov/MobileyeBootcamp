#include "CameraProcessor.h" 

using namespace cv;

//c'tor
CameraProcessor::CameraProcessor(string _path, int numFrames, double frameDiff){
	countFrame = 0;
	active = true;
	capture.open(path);
	numFramesCheck = numFrames;
	frameDiffThreshold = frameDiff;
}

//d'tor
CameraProcessor::~CameraProcessor() {
	capture.release();
}

bool CameraProcessor::calcAbsDiff() {
	Mat diff;
	absdiff(prev, frameWrap.image, diff);

	//convert diff to gray because countNonZero func can't to resive COLOR_IMG 
	cvtColor(diff, diff, COLOR_BGR2GRAY);
	double normalRes = (double)(countNonZero(diff)) / (double)(frameWrap.image.cols * frameWrap.image.rows);

	return frameDiffThreshold < normalRes;
}

void CameraProcessor::run() {

	connectionManager connect("localhost:50051");

	while (active) {

		capture.read(frameWrap.image);

		if (frameWrap.image.empty()) {
			cout << "End of stream\n";
			Logger::Info("End of stream");
			break;
		}
		
		if (++countFrame == 1||(countFrame % numFramesCheck == 0 && calcAbsDiff())) {
			frameWrap.frameNumber = countFrame;
			frameWrap.timestamp = currentTime();
			this_thread::sleep_for(chrono::milliseconds(333));
			connect.sendToServer(frameWrap);
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

int CameraProcessor::getId() {
	return cameraId;
}

void CameraProcessor::setFrame(Mat p) {
	frameWrap.image = p;
};

void CameraProcessor::setPrev(Mat& p) {
	prev = p;
};




connectionManager::connectionManager(const std::string& server_address): stub_(CameraService::NewStub(grpc::CreateChannel(server_address,grpc::InsecureChannelCredentials()))){}

void connectionManager::sendToServer(FrameWrap& frameWrap) {

	CameraDataRequest request;
	CameraDataResponse response;
	grpc::ClientContext context;

	vector<uchar> image_data;
	imencode(".jpg", frameWrap.image, image_data);

	request.set_image(image_data.data(), image_data.size());
	request.set_timestamp(frameWrap.timestamp);
	request.set_framenumber(frameWrap.frameNumber);

	grpc::Status status = stub_->SendCameraData(&context, request, &response);

	if (status.ok()) {
		cout << "Server response: " << response.acknowledgment() << endl;
		Logger::Info("send to server");
	}
	else {
		cerr << "RPC failed: " << status.error_message() << endl;
		Logger::Error("send to server is failed");
	}
}