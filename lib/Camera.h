# include "Header.h"
#include <conio.h>


void cameraPart(queue<FrameWrap>& dataFromCamera);
string currentTime();

class CameraProcessor {

private:

    int numFramesCheck;

    int countFrame;

    int cameraId;

    double frameDiffThreshold;

    bool active;

    FrameWrap frame;

    queue<FrameWrap>& dataFromCamera;

    bool calcAbsDiff();

    Mat prev;
   

public:
   CameraProcessor(queue<FrameWrap>& queue);

   void setCountFrame();

   int getCountFrame();

    VideoCapture capture;

	void init(int id ,string path,int numFrames, double frame_diff);

    void insertToQueue();

    void run();
};

