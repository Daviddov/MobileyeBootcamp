#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

#include "Queue.h"

#include <chrono>
#include <thread>
#include <memory>
#include <opencv2/opencv.hpp>
#include "../sqlite3/sqlite3.h"
#include "../lib_logger/Logger.h"


#include <ctime>
#include <iomanip>
#include <sstream>



//using namespace cv;
using namespace std;

struct Detection
{
    int class_id;
    float confidence;
    cv::Rect box;
};

struct FrameWrap
{
    cv::Mat image;
    string timestamp;
    int frameNumber;
};



struct GetFromDataBase {
    int id;
    string time;
    cv::Rect rect;
    FrameWrap fw;
    string typeObject;
    float r, g, b;
};








