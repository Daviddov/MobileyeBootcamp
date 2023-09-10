#pragma once
#include "Header.h"
#include <grpc++/grpc++.h>
#include "../protos/service.grpc.pb.h"



class ListeningManager final : public services::CameraService::Service {

private:

	Queue<FrameWrap>& dataFromCamera;

public:

	ListeningManager(Queue<FrameWrap>& queue);

	grpc::Status SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) override;
};

    void startListen(Queue<FrameWrap>& dataFromCamera);
	