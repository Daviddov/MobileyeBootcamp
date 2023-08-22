# include "Header.h"
#include "Yolo.h"
#include "Rect.h"
#include <conio.h>

class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	queue<FrameWrap>& dataFromCamera;

	SQLHandler sqlHandler;

	Yolo5 yolo;

public:

	ServerProcessor(queue<FrameWrap>& dataFromCamera);
	~ServerProcessor();
	void detect_with_YOLO5();

	void run();

  static void  serverPart(ServerProcessor& server);
};
