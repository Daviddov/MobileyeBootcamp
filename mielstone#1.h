#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/core/mat.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp >
#include <filesystem>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

struct Detection
{
    int class_id;
    float confidence;
    Rect box;
};

bool calcAbsDiff(const  Mat& image1, const Mat& image2);

void writeHeaderToFile();

void writeRectOnCSV(const Mat& org, Rect rect, double timestamp, string objectType);

void calcAvgPerChanel(const Mat& img, float* B, float* G, float* R);

Mat format_yolov5(const Mat& src);

void detect(cv::Mat& image, dnn::Net& net, vector<Detection>& output, const vector<string>& className);

void toDrawRect(Mat& image, vector<Detection>& output, const vector<string>& className, double timestamp);

vector<string> load_class_list();

void load_net(cv::dnn::Net& net);