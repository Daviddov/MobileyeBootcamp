#pragma once
#include <opencv2/opencv.hpp>
struct Detection
{
    int class_id;
    float confidence;
    cv::Rect box;
};