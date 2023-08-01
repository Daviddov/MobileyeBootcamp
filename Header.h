#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>
#include "sqlite_build/src/sqlite3.h"
#include <format>

using namespace cv;
using namespace std;

struct Detection
{
    int class_id;
    float confidence;
    Rect box;
};

bool calcAbsDiff(const  Mat& image1, const Mat& image2);

void detect_with_YOLO5(Mat currFrame, double timestamp);

void writeRectOnDB(const Mat& org, Rect rect, double timestamp, string objectType);

bool handleDBError(int failed, sqlite3* db, string what);

void calcAvgPerChanel(const Mat& img, float* B, float* G, float* R);

Mat format_yolov5(const Mat& src);

void detect(cv::Mat& image, dnn::Net& net, vector<Detection>& output, const vector<string>& className);

void toDrawRect(Mat& image, vector<Detection>& output, const vector<string>& className, double timestamp);

vector<string> load_class_list();

void load_net(cv::dnn::Net& net);
