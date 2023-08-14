
#include "lib/Camera.h"
#include "lib/Server.h"

//something instead waitKey for exit from while(true) in camera part.
//mutex!!!!!!!!!!!!



int main() {

	queue<FrameWrap> dataFromCamera;

	thread cameraThread(cameraPart, ref(dataFromCamera));

	thread serverThread(serverPart, ref(dataFromCamera));

	cameraThread.join();
	serverThread.join();
	
	return 0;
}

