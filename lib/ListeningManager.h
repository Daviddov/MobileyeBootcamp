#pragma once
#include "Header.h"
#include "../proto_gen/camera_service.grpc.pb.h"
#include <grpc++/grpc++.h>



class ListeningManager final : public services::CameraService::Service {

private:

	Queue<FrameWrap>& dataFromCamera;

public:

	ListeningManager(Queue<FrameWrap>& queue);

	grpc::Status SendCameraData(grpc::ServerContext* context, const services::CameraDataRequest* request, services::CameraDataResponse* response) override;
};

    void startListen(Queue<FrameWrap>& dataFromCamera);
	