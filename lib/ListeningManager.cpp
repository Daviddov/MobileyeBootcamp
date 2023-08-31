#include "ListeningManager.h"

ListeningManager::ListeningManager(queue<FrameWrap>& queue) :dataFromCamera(queue) {
	numOfCameras = 0;
}

ListeningManager::~ListeningManager() {

	for (int i = 0; i < cameras.size(); i++) {
		Logger::Debug("The heap memory of camera id: %d deleted", cameras[i]->getId());
		delete cameras[i];
	}
}

void ListeningManager::addCamera(int id, string path) {

	//??? need to replace it to shear ptr ???
	CameraProcessor* camera = new CameraProcessor(dataFromCamera, id, path);

	cameras.push_back(camera);
	numOfCameras++;
}

void ListeningManager::removeCamera(int id) {
	if (numOfCameras == 0) return;

	for (auto camera = cameras.begin(); camera != cameras.end();) {
		if ((*camera)->getId() == id) {
			cameras.erase(camera);
			delete* camera;
			Logger::Debug("The heap memory of camera id: %d deleted", id);
			break;
		}
		else {
			camera++;
		}
	}
	numOfCameras--;
}

void ListeningManager::startListen(ListeningManager listen) {
	
	VideoCapture capture;
	capture.open("C:\\Users\\1\\Desktop\\project_files\\parking.mp4");
	if (!capture.isOpened()) {
		cout<< "Error opening video file"<<endl;
	}
	int count = 0;
	while (true) {
		FrameWrap frameWrap;
		capture.read(frameWrap.image);
		frameWrap.frameNumber = 123;
		frameWrap.timestamp = "123";

		FrameWrap temp = frameWrap;
		temp.image = frameWrap.image.clone();

		if(count%20 == 0)
		listen.dataFromCamera.push(temp);
		count++;
	}

	//detach to causes it the thread continu after the function finished
	//cameraThread.detach();


	//string server_address("0.0.0.0:50051");
	//CameraServiceImpl service(dataFromCamera);

	//grpc::ServerBuilder builder;
	//builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	//builder.RegisterService(&service);

	//unique_ptr<grpc::Server> server(builder.BuildAndStart());
	//cout << "Server listening on " << server_address << endl;
	//server->Wait();
	
}


//c'tor
//CameraServiceImpl::CameraServiceImpl(queue<FrameWrap>& queue) :dataFromCamera(queue) {}
//
//grpc::Status CameraServiceImpl:: SendCameraData(grpc::ServerContext* context,const CameraDataRequest* request,CameraDataResponse* response) { 
//
//	frameWrap.frameNumber = request->frameNumber;
//	frameWrap.timestamp = request->timestamp;
// 
// //here need to replace to Mat
//	frameWrap.image = request->image;
//
//  //using in temp
//	dataFromCamera.push(frameWrap);
//
//	response->set_acknowledgment("successfully.");
//	return grpc::Status::OK;
//}
//



