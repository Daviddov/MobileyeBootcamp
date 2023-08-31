#pragma once
#include "Camera.h"
#include "Server.h"


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