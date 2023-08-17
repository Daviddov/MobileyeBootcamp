
# include "Header.h"
#include <conio.h>



class ServerProcessor {

private:

	bool active;

	FrameWrap currFrame;

	queue<FrameWrap>& dataFromCamera;


public:

	ServerProcessor(queue<FrameWrap>& dataFromCamera);

	void detect_with_YOLO5(FrameWrap& currFrame);

	void run();

};

    void serverPart(ServerProcessor& server);