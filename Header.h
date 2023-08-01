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
#include "sqlite_build/src/sqlite3.h"


using namespace cv;
using namespace std;

struct Detection
{
    int class_id;
    float confidence;
    Rect box;
};

bool calcAbsDiff(const  Mat& image1, const Mat& image2);

void detect_with_YOLO5(Mat currFrame, string timestamp, int frameNumber);

void writeRectOnDB(const Mat& org, Rect rect, string timestamp, string objectType, int frameNumber);

bool handleDBError(int failed, sqlite3* db, string what);

void calcAvgPerChanel(const Mat& img, float* B, float* G, float* R);

Mat format_yolov5(const Mat& src);

void detect(cv::Mat& image, dnn::Net& net, vector<Detection>& output, const vector<string>& className);

void toDrawRect(Mat& image, vector<Detection>& output, const vector<string>& className, string timestamp, int frameNumber);

vector<string> load_class_list();

void load_net(cv::dnn::Net& net);

static int callbackFunction(void* data, int argc, char** argv, char** azColName); 

string currentTime();
