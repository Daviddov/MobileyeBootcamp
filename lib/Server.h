# include "Header.h"
#include "Yolo.h"
#include "Rect.h"
#include <conio.h>
#include "Camera.h"
class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	queue<FrameWrap>& dataFromCamera;

	SQLHandler sqlHandler;

public:

	ServerProcessor(queue<FrameWrap>& dataFromCamera);

	void detect_with_YOLO5(Yolo5 yolo);

	void run();

  static void  serverPart(ServerProcessor& server);
};
