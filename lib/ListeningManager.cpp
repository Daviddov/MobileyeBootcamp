#include "ListeningManager.h"
#include "ConfigurationManager.h"

using namespace cv;

ListeningManager::ListeningManager(Queue<FrameWrap>& queue) :dataFromCamera(queue) {}

grpc::Status ListeningManager::SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) {

	FrameWrap frameWrap;
	frameWrap.frameNumber = request->framenumber();
	frameWrap.timestamp = request->timestamp();

	const string& imageDataString = request->image();
	vector<uint8_t> imageData(imageDataString.begin(), imageDataString.end());
	frameWrap.image = imdecode(imageData, IMREAD_COLOR);

	dataFromCamera.push(frameWrap);

	response->set_acknowledgment("successfully.");
	return grpc::Status::OK;
}



void startListen(Queue<FrameWrap>& dataFromCamera) {
	ConfigurationManager configManager;
	string server_address = configManager.getFieldValue<string>("backendIP");

	ListeningManager service(dataFromCamera);

	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);

	unique_ptr<grpc::Server> server(builder.BuildAndStart());
	cout << "Server listening on " << server_address << endl;
	server->Wait();
}



