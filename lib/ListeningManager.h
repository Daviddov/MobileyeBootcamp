#pragma once
#include "Header.h"
#include "../proto_gen/camera_service.grpc.pb.h"
#include <grpc++/grpc++.h>



class ListeningManager final : public CameraService::Service {

private:

	Queue<FrameWrap>& dataFromCamera;

public:

	ListeningManager(Queue<FrameWrap>& queue);

	grpc::Status SendCameraData(grpc::ServerContext* context, const CameraDataRequest* request, CameraDataResponse* response) override;
};

    void startListen(Queue<FrameWrap>& dataFromCamera);
	