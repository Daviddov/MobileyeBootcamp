# include "Header.h"
#include <conio.h>




class CameraProcessor {

private:

    int numFramesCheck;

    int countFrame;

    int cameraId;

    double frameDiffThreshold;

    bool active;

    FrameWrap frame;

    queue<FrameWrap>& dataFromCamera;

    Mat prev;
   
    VideoCapture capture;

public:

   CameraProcessor(queue<FrameWrap>& queue);

    bool calcAbsDiff();

    void setFrame(Mat f);

    void setPrev(Mat p);

    void  setNumFramesCheck(double p);

	void init(int id ,string path,int numFrames, double frame_diff);

    void insertToQueue();

    void run();
};

void cameraPart(CameraProcessor& camera);

string currentTime();