#include "Yolo.h"


using namespace std::chrono;

Yolo5::Yolo5() {
    loadNet();
    loadClassList();
    
     INPUT_SIZE = 640.0f;
     SCORE_THRESHOLD = 0.2f;
     NMS_THRESHOLD = 0.4f;
     CONFIDENCE_THRESHOLD = 0.1f;

     NUM_OF_DETECT = 25200;
     NUM_OF_DATA = 85;
}

void Yolo5::loadClassList() {
    ifstream classFile("./assets/classes.txt");
    string line;
    while (getline(classFile, line)) {
        classList.push_back(line);
    }
    Logger::Info("Class list loaded for YOLO.");
}

void Yolo5::loadNet() {
    net = dnn::readNet("./assets/yolov5n.onnx");

    cout << "Running on CPU\n";
    net.setPreferableBackend(dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(dnn::DNN_TARGET_CPU);
}

Mat Yolo5::formatInputImage() {
    int maxDimension = MAX(frameWarp.image.cols, frameWarp.image.rows);
    Mat result = Mat::zeros(maxDimension, maxDimension, CV_8UC3);
    frameWarp.image.copyTo(result(Rect(0, 0, frameWarp.image.cols, frameWarp.image.rows)));
    return result;
}

void Yolo5::detect() {
 
    Mat blob;

    Mat inputImage = formatInputImage();
    dnn::blobFromImage(inputImage, blob, 1. / 255., Size(INPUT_SIZE, INPUT_SIZE), Scalar(), true, false);
    net.setInput(blob);
    vector<Mat> outputs;
    
  
    net.forward(outputs, net.getUnconnectedOutLayersNames());
   

    float xFactor = inputImage.cols / INPUT_SIZE;
    float yFactor = inputImage.rows / INPUT_SIZE;

    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;

    float* data = (float*)outputs[0].data;

    for (int i = 0; i < NUM_OF_DETECT; ++i) {
        float confidence = data[4];
        if (confidence >= CONFIDENCE_THRESHOLD) {
            float* classesScores = data + 5;
            Mat scores(1, classList.size(), CV_32FC1, classesScores);
            Point classId;
            double maxClassScore;
            minMaxLoc(scores, 0, &maxClassScore, 0, &classId);
           
            if (maxClassScore > SCORE_THRESHOLD && (classId.x == CAR || classId.x == MOTORBIKE || classId.x == BUS || classId.x == TRUCK)) {
                confidences.push_back(confidence);
                classIds.push_back(classId.x);

                float x = data[0];
                float y = data[1];
                float w = data[2];
                float h = data[3];

                int left = int((x - 0.5 * w) * xFactor);
                int top = int((y - 0.5 * h) * yFactor);
                int width = int(w * xFactor);
                int height = int(h * yFactor);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
        data += NUM_OF_DATA;
    }
    vector<int> nmsResult;
    dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nmsResult);
  
    output.clear();


    for (int i = 0; i < nmsResult.size(); i++) {
        int idx = nmsResult[i];
        Detection result;
        result.class_id = classIds[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }


}

vector<Detection>& Yolo5::getOutput() {
    return output;
}

vector<string>& Yolo5::getClassList() {
    return classList;
}

void Yolo5::setFrame(FrameWrap& currFrame) {
    frameWarp = currFrame;
}



