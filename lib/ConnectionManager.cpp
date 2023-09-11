
#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(const string& server_address) : stub(CameraService::NewStub(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()))) {
	countTryToConnect = 0;
}

void ConnectionManager::sendToServer(FrameWrap frameWrap) {

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
		cout << "Server response: " << response.acknowledgment() << endl;
	}
	else {
		cerr << "RPC failed: " << status.error_message() << endl;
		countTryToConnect++;
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}