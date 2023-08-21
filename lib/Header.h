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
#include "../lib_logger/Logger.h"




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
    int frameNumber;
};








