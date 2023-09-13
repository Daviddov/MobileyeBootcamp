#pragma once
#include "Header.h"
#include <grpc++/grpc++.h>
#include "../protos/service.grpc.pb.h"



class ServerListeningManager final : public services::CameraService::Service {

private:

	Queue<FrameWrap>& dataFromCamera;

	condition_variable& conditionVar;

public:

	ServerListeningManager(Queue<FrameWrap>& queue,condition_variable& condition);

	grpc::Status SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) override;

    void startListen();
};

	