#pragma once 

#include <opencv2/opencv.hpp>
#include <string>

// Define your FrameWrap class
class FrameWrap {
public:
    // Define members and methods of FrameWrap here

    cv::Mat image;
    std::string timestamp;
    int frameNumber;

    // Custom comparison operator for FrameWrap
    bool operator==(const FrameWrap& other) const {
        // Customize this comparison based on your requirements
        if (frameNumber == other.frameNumber && timestamp == other.timestamp) {
            cv::Mat diff;
            cv::absdiff(image, other.image, diff);
            return cv::countNonZero(diff) == 0; // Compare if the difference matrix is all zeros
        }
        return false;
    }
};
