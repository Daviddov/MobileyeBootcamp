#include "../protos/service.grpc.pb.h"
#include <grpc++/grpc++.h>
#include "CameraProcessor.h"

using services::CameraService;
using services::CameraDataRequest;
using services::CameraDataResponse;


class ConnectionManager {

public:

	ConnectionManager(const string& server_address);

	void sendToServer(FrameWrap frameWrap);

	int countTryToConnect;

private:

	unique_ptr<services::CameraService::Stub> stub;
};
