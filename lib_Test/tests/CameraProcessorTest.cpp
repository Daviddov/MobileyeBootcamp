#include "CameraProcessor.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"



//TEST(CalcAbsDiffTest, TestCalcAbsDiff) {
//
//    Mat testImage1(3, 3, CV_8UC3, Scalar(100, 150, 200));
//    Mat testImage2(3, 3, CV_8UC3, Scalar(100, 150, 200));
//
//    Queue<FrameWrap> queue;
//    CameraProcessor camera(queue, 2, "123");
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
//    camera.setFrame(testImage3);
//    camera.setPrev(testImage4);
//
//    ASSERT_TRUE(camera.calcAbsDiff());
//}


TEST(CurrentTimeTest, TestCurrentTime) {
    // Get the current system time using the C++ standard library
    auto now = chrono::system_clock::now();
    time_t timestamp = chrono::system_clock::to_time_t(now);
    tm timeinfo;

    // Use thread-safe version of localtime
#ifdef _WIN32
    localtime_s(&timeinfo, &timestamp);
#else
    localtime_r(&timestamp, &timeinfo);
#endif
    char buffer[28];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    // Calculate milliseconds
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));

    string expected_formatted_time = buffer;

    // Call the currentTime function to get the result
    string actual_formatted_time = currentTime();

    // Calculate the absolute difference in milliseconds
    int expected_milliseconds = stoi(expected_formatted_time.substr(20, 3));
    int actual_milliseconds = stoi(actual_formatted_time.substr(20, 3));
    int time_difference = abs(expected_milliseconds - actual_milliseconds);

    // Check if the time difference is less than 5 milliseconds
    ASSERT_LE(time_difference, 5);
}

