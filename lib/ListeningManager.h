#pragma once
#include "Camera.h"
#include "Server.h"


class ListeningManager {

private:

	queue<FrameWrap>& dataFromCamera;

	int numOfCameras;

public:

	vector<CameraProcessor*> cameras;

	ListeningManager(queue<FrameWrap>& queue);

	~ListeningManager();

	void addCamera(int id, string path);

	void removeCamera(int id);

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
//    FrameWrap frameWrap;
//
//	grpc::Status SendCameraData(grpc::ServerContext* context,const CameraDataRequest* request,CameraDataResponse* response) override;
//
//
//};