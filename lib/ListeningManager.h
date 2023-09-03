#pragma once
#include "CameraProcessor.h"
#include "Server.h"
#include "camera_service.grpc.pb.h"
#include <grpc++/grpc++.h>

class ListeningManager {

private:

	Queue<FrameWrap>& dataFromCamera;

public:

	vector<CameraProcessor*> cameras;

	ListeningManager(Queue<FrameWrap>& queue);

	~ListeningManager();

	static void startListen(ListeningManager listen);

};


//class CameraServiceImpl final : public CameraService::Service {
//
//public:
//
//	queue<FrameWrap>& dataFromCamera;
//
//	CameraServiceImpl(queue<FrameWrap>& queue);
//
//  FrameWrap frameWrap;
//
//	grpc::Status SendCameraData(grpc::ServerContext* context,const CameraDataRequest* request,CameraDataResponse* response) override;
//
//
//};