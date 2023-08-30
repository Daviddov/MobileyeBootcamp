#pragma once
#include "Camera.h"
#include "Server.h"


class CameraManager {

private:

	Queue<FrameWrap>& dataFromCamera;


	int numOfCameras;

public:

	vector<CameraProcessor*> cameras;

	CameraManager(Queue<FrameWrap>& queue);

	~CameraManager();

	void addCamera(int id, string path);

	void removeCamera(int id);

	void startCameraRun(int id);


};