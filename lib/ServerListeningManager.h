#pragma once
//#include "Header.h"
#include <grpc++/grpc++.h>
#include "../thirdParty/protos/service.grpc.pb.h"
#include "ConfigurationManager.h"
#include "QueueSafe.h"
#include "FrameWarp.h"

using namespace std;

class ServerListeningManager final : public services::CameraService::Service {

private:

	QueueSafe<FrameWrap>& dataFromCamera;

	condition_variable& conditionVar;

public:

	ServerListeningManager(QueueSafe<FrameWrap>& queue,condition_variable& condition);

	grpc::Status SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) override;

    void startListen();
};

	