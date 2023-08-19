
#include "lib/Camera.h"
#include "lib/Server.h"

//something instead waitKey for exit from while(true) in camera part and server part(if size == 0).
//mutex!!!!!!!!!!!!



int main() {

	queue<FrameWrap> dataFromCamera;

	CameraProcessor camera(dataFromCamera);

	ServerProcessor server(dataFromCamera);

	thread cameraThread(camera.cameraPart, ref(camera));
	
	thread serverThread(server.serverPart, ref(server));

	cameraThread.join();
	serverThread.join();
	
	return 0;
}

