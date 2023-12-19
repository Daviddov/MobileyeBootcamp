
#include "CameraConnectionManager.h"

CameraConnectionManager::CameraConnectionManager(const string& server_address) : stub(CameraService::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()))) {
	countTryToConnect = 0;
	Logger::Info("port:", server_address);
}

void CameraConnectionManager::sendToServer(FrameWrap& frameWrap) {

	CameraDataRequest request;
	CameraDataResponse response;
	grpc::ClientContext context;

	vector<uchar> image_data;
	imencode(".jpg", frameWrap.image, image_data);

	request.set_image(image_data.data(), image_data.size());
	request.set_timestamp(frameWrap.timestamp);
	request.set_framenumber(frameWrap.frameNumber);

	grpc::Status status = stub->SendCameraData(&context, request, &response);
	
	if (status.ok()) {
		Logger::Info("Server response: " , response.acknowledgment());
	}
	else {


		Logger::Info("RPC failed: " , status.error_message());
		countTryToConnect++;
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}