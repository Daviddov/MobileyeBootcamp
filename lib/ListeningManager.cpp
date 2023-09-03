#include "ListeningManager.h"
using namespace cv;
ListeningManager::ListeningManager(Queue<FrameWrap>& queue) :dataFromCamera(queue) {}

ListeningManager::~ListeningManager() {}

void ListeningManager::startListen(ListeningManager listen) {
	//From here /////////////////////////////////////
   	VideoCapture capture;                          //
	capture.open("./assets/parking.mp4");          //
	if (!capture.isOpened()) {                     //
		cout<< "Error opening video file"<<endl;   //
	}                                              //
	int count = 0;                                 // 
	while (true) {                                 //
		FrameWrap frameWrap;                       //
		capture.read(frameWrap.image);             // 
		frameWrap.frameNumber = 123;               //
		frameWrap.timestamp = "123";               //
		                                           //
		FrameWrap temp = frameWrap;                //
		temp.image = frameWrap.image.clone();      //
		                                           //
		if(count%20 == 0)                          //
		listen.dataFromCamera.push(temp);          //
		count++;                                   //
	}                                              //
	 ////until here is a temporary until fixed grpc//
	  

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
// FrameWrap frameWrap;
// 
//	frameWrap.frameNumber = request->frameNumber;
//	frameWrap.timestamp = request->timestamp;
// 
// //here need to replace to Mat
//
    /*  const string& imageDataString = request->image();
     vector<uint8_t> imageData(imageDataString.begin(), imageDataString.end());
	 frameWrap.image = imdecode(imageData,IMREAD_COLOR);*/

//	
//
//  //does need to using in temp??
//	dataFromCamera.push(frameWrap);
//
//	response->set_acknowledgment("successfully.");
//	return grpc::Status::OK;
//}
//



