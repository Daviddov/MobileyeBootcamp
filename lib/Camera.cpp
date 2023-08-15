#include "Camera.h" 




void cameraPart(queue<FrameWrap>& dataFromCamera, bool &active) {
    FrameWrap frame;

    VideoCapture capture(R"(./assets/parking.mp4)");
    if (!capture.isOpened()) {
        cerr << "\nError opening video file\n";
        return;
    }

    capture.read(frame.image);

    int count_frames = 1;

    frame.frameNamber = count_frames;
    frame.timestamp = currentTime();

    dataFromCamera.push(frame);

    Mat prev = frame.image;

    while (active) {
        FrameWrap frame;

        capture.read(frame.image);

        frame.timestamp = currentTime();

        frame.frameNamber = ++count_frames;

        if (frame.image.empty()) {
            cout << "End of stream\n";
            break;
        }

        if (frame.frameNamber % 30 == 0 && calcAbsDiff(prev, frame.image)) {
            prev = frame.image;
            dataFromCamera.push(frame);
            cout << "pushing!!!!!!!!!!!" << endl;
        }
        else {
            // cout << "rejected!!!!!!!!!!!" << endl;
            continue;
        }
        cout << "part camera\n";
       
       
    }
}
