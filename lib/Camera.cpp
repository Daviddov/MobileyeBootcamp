#include "Camera.h" 

void CameraProcessor::setFrame(Mat f) {
    frame.image = f;
}

void CameraProcessor::setPrev(Mat p) {
    prev = p;
}
void  CameraProcessor::setNumFramesCheck(double p) {
    numFramesCheck = p;
}

//c'tor
CameraProcessor::CameraProcessor(queue<FrameWrap>& queue) : dataFromCamera(queue){
    countFrame = 0;
    active = true;
    cameraId = 0;
    numFramesCheck = 0;
    frameDiffThreshold = 0;
}

bool CameraProcessor:: calcAbsDiff() {
    Mat diff;
    absdiff(prev, frame.image, diff);

    //convert diff to gray because countNonZero func can't to resive COLOR_IMG 
    cvtColor(diff, diff, COLOR_BGR2GRAY);
    double normalRes = (double)(countNonZero(diff)) / (double)(frame.image.cols * frame.image.rows);
    return frameDiffThreshold < normalRes;
}

void CameraProcessor::init(int id,string path,int numFrames ,double frame_diff) {

    cameraId = id;

    numFramesCheck = numFrames;

    frameDiffThreshold = frame_diff;

    capture.open(path);

    if (!capture.isOpened()) {
        cerr << "\nError opening video file\n";
        return;
    }
    capture.read(frame.image);
}

void CameraProcessor::insertToQueue() {

    frame.frameNamber = ++countFrame;

    frame.timestamp = currentTime();

    FrameWrap temp = frame;
    temp.image = frame.image.clone();
    dataFromCamera.push(temp);

     prev = frame.image.clone();
}

void CameraProcessor::run() {

    while (active) {
       
        capture.read(frame.image);
      
        if (frame.image.empty()) {
            cout << "End of stream\n";
            break;
        }
        if (++countFrame % numFramesCheck == 0 &&calcAbsDiff()) {
            insertToQueue();
        }
        else {
            continue;
        }
        cout << "part camera\n";
    }
}

string currentTime() {

    auto timestamp = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()
    ).count();

    int milliseconds = timestamp % 1000;

    time_t time_t_timestamp = timestamp / 1000;

    tm timeinfo;
    localtime_s(&timeinfo, &time_t_timestamp);

    char buffer[28];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", milliseconds);

    string formatted_time = buffer;
    return formatted_time;
}

void CameraProcessor::cameraPart(CameraProcessor& camera) {

    //the user input it using Qt
    int id = 123;

    //the user input it using Qt
    int numFrames = 30;

    //the user input it using Qt
    double frameDiffThreshold = 0.9;

    //the user input it using Qt
    string path = R"(./assets/parking.mp4)";
    //string path = R"(C:\Users\1\Desktop\project_files\police.mp4)";

    camera.init(id,path, numFrames, frameDiffThreshold);

    camera.insertToQueue();

    camera.run();
}
