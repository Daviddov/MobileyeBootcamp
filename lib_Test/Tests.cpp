#include "../lib/Header.h"
#include "../lib/Camera.h"
#include "../lib/Rect.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"
#include "gmock/gmock.h"


//TEST(CalcAbsDiffTest, TestCalcAbsDiff) {
//
//    Mat testImage1(3, 3, CV_8UC3, Scalar(100, 150, 200));
//    Mat testImage2(3, 3, CV_8UC3, Scalar(100, 150, 200));
//
//    queue<FrameWrap> queue;
//    CameraProcessor camera(queue,2,"123");
//
//    camera.setFrameDiffThreshold(0.9);
//    camera.setFrame(testImage1);
//    camera.setPrev(testImage2);
//
//
//    ASSERT_FALSE(camera.calcAbsDiff());
//
//    Mat testImage3(3, 3, CV_8UC3, Scalar(100, 150, 200));
//    Mat testImage4(3, 3, CV_8UC3, Scalar(110, 160, 210));
//
//
//    camera.setFrame(testImage3);
//    camera.setPrev(testImage4);
//
//    ASSERT_TRUE(camera.calcAbsDiff());
//}



//#ifdef _WIN32
//// Windows-specific includes
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#else
//// Linux-specific includes
//#include <unistd.h>
//#endif
//
//std::string currentTime() {
//    auto now = std::chrono::system_clock::now();
//    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
//    std::tm timeinfo;
//
//    // Use thread-safe version of localtime
//#ifdef _WIN32
//    localtime_s(&timeinfo, &timestamp);
//#else
//    localtime_r(&timestamp, &timeinfo);
//#endif
//
//    char buffer[28];
//    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
//
//    // Calculate milliseconds
//    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
//    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));
//
//    std::string formatted_time = buffer;
//    return formatted_time;
//}
//
//TEST(CurrentTimeTest, TestCurrentTime) {
//    // Get the current system time using the C++ standard library
//    auto now = std::chrono::system_clock::now();
//    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
//    std::tm timeinfo;
//
//    // Use thread-safe version of localtime
//#ifdef _WIN32
//    localtime_s(&timeinfo, &timestamp);
//#else
//    localtime_r(&timestamp, &timeinfo);
//#endif
//
//    char buffer[28];
//    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
//
//    // Calculate milliseconds
//    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
//    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));
//
//    std::string expected_formatted_time = buffer;
//
//    // Call the currentTime function to get the result
//    std::string actual_formatted_time = currentTime();
//
//    // Calculate the absolute difference in milliseconds
//    int expected_milliseconds = std::stoi(expected_formatted_time.substr(20, 3));
//    int actual_milliseconds = std::stoi(actual_formatted_time.substr(20, 3));
//    int time_difference = std::abs(expected_milliseconds - actual_milliseconds);
//
//    // Check if the time difference is less than 5 milliseconds
//    ASSERT_LE(time_difference, 5);
//}
//
