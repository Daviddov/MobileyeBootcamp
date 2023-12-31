#include <grpc++/grpc++.h>
#include "CameraProcessor.h"
#include "../thirdParty/protos/service.grpc.pb.h"

using services::CameraService;
using services::CameraDataRequest;
using services::CameraDataResponse;


class CameraConnectionManager {

public:

	CameraConnectionManager(const string& server_address);

	void sendToServer(FrameWrap &frameWrap);

	int countTryToConnect;

private:

	unique_ptr<services::CameraService::Stub> stub;
};
