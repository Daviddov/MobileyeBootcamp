#include "ListeningManager.h"

using namespace cv;

ListeningManager::ListeningManager(Queue<FrameWrap>& queue, condition_variable& condition) :dataFromCamera(queue), conditionVar(condition) {}

grpc::Status ListeningManager::SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) {

	FrameWrap frameWrap;
	frameWrap.frameNumber = request->framenumber();
	frameWrap.timestamp = request->timestamp();

	const string& imageDataString = request->image();
	vector<uint8_t> imageData(imageDataString.begin(), imageDataString.end());
	frameWrap.image = imdecode(imageData, IMREAD_COLOR);

	dataFromCamera.push(frameWrap);
	conditionVar.notify_one();

	response->set_acknowledgment("successfully.");
	return grpc::Status::OK;
}



void ListeningManager::startListen() {

	string server_address("0.0.0.0:50051");

	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(this);

	unique_ptr<grpc::Server> server(builder.BuildAndStart());
	cout << "Server listening on " << server_address << endl;
	server->Wait();
}



