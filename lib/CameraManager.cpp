#include "CameraManager.h"

CameraManager::CameraManager(queue<FrameWrap>& queue) :dataFromCamera(queue) {
	numOfCameras = 0;
}

CameraManager::~CameraManager() {

	for (int i = 0; i < cameras.size(); i++) {
		Logger::Info("The heap memory of camera id: %d deleted", cameras[i]->getId());
		delete cameras[i];
	}
}

void CameraManager::addCamera(int id, string path) {

	//??? need to replace it to shear ptr ???
	CameraProcessor* camera = new CameraProcessor(dataFromCamera, id, path);

	cameras.push_back(camera);
	numOfCameras++;
}

void CameraManager::removeCamera(int id) {
	if (numOfCameras == 0) return;

	for (auto camera = cameras.begin(); camera != cameras.end();) {
		if ((*camera)->getId() == id) {
			cameras.erase(camera);
			delete* camera;
			Logger::Info("The heap memory of camera id: %d deleted", id);
			break;
		}
		else {
			camera++;
		}
	}
	numOfCameras--;
}

void CameraManager::startCameraRun(int id) {
	int index = 0;
	for (int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i]->getId() == id) {
			index = i;
			break;
		}
	}
	thread cameraThread(CameraProcessor::cameraPart, cameras[index]);

	//detach to causes it the thread continu after the function finished
	cameraThread.detach();
}