#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>
#include "../sqlite3/sqlite3.h"



using namespace cv;
using namespace std;

struct Detection
{
    int class_id;
    float confidence;
    Rect box;
};

struct FrameWrap
{
    Mat image;
    string timestamp;
    int frameNamber;
};

void detect_with_YOLO5( FrameWrap& currFrame);

vector<string> load_class_list();

void load_net(cv::dnn::Net& net);
Mat format_yolov5(const Mat& src);
void detect(Mat& image, dnn::Net& net, vector<Detection>& output, const vector<string>& className);
void toDrawRect(const FrameWrap& currFrame, vector<Detection>& output, const vector<string>& className);
void writeRectOnDB(const FrameWrap& currFrame, Rect rect, string objectType);
void calcAvgPerChanel(const Mat& img, float* B, float* G, float* R);
string currentTime();
bool calcAbsDiff(const  Mat& image1, const Mat& image2);

static int callbackFunction(void* data, int argc, char** argv, char** azColName);

bool handleDBError(int failed, sqlite3* db, string what);







