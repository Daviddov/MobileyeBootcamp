#pragma once
#include "Header.h"
#include "../protos/service.grpc.pb.h"
#include <grpc++/grpc++.h>



class ListeningManager final : public services::CameraService::Service {

private:

	Queue<FrameWrap>& dataFromCamera;

	condition_variable& conditionVar;

public:

	ListeningManager(Queue<FrameWrap>& queue,condition_variable& condition);

	grpc::Status SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) override;

    void startListen();
};

	