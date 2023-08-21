# include "Header.h"
#include <conio.h>
#include "SQLHandler.h"




class CameraProcessor {

private:

	int countFrame;

	int cameraId;

	int numFramesCheck;

	double frameDiffThreshold;

	bool active;

	FrameWrap frameWarp;

	queue<FrameWrap>& dataFromCamera;

	Mat prev;

	VideoCapture capture;

public:

	CameraProcessor(queue<FrameWrap>& queue);

	~CameraProcessor();

	bool calcAbsDiff();

	void setFrame(Mat f);

	void setPrev(Mat p);

	void  setFrameDiffThreshold(double frameDiff);

	void init(int id, string path, int numFrames, double frame_diff);

	void insertToQueue();

	void run();

	static void  cameraPart(CameraProcessor& camera);
};


string currentTime();