#include "../lib/Header.h"
#include "../lib/Camera.h"
#include "../lib/Rect.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"




//TEST(TestCaseName, TestName) {
//
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//}
//
//    EXPECT_EQ(1, 1);
//    EXPECT_TRUE(true);
//}

TEST(CalcAbsDiffTest, TestCalcAbsDiff) {

    Mat testImage1(3, 3, CV_8UC3, Scalar(100, 150, 200));
    Mat testImage2(3, 3, CV_8UC3, Scalar(100, 150, 200));

    queue<FrameWrap> queue;
    CameraProcessor camera(queue);

    camera.setFrameDiffThreshold(0.9);
    camera.setFrame(testImage1);
    camera.setPrev(testImage2);


    ASSERT_FALSE(camera.calcAbsDiff());

    Mat testImage3(3, 3, CV_8UC3, Scalar(100, 150, 200));
    Mat testImage4(3, 3, CV_8UC3, Scalar(110, 160, 210));


    camera.setFrame(testImage3);
    camera.setPrev(testImage4);

    ASSERT_TRUE(camera.calcAbsDiff());
}

TEST(InsertToQueueTest, BasicFunctionality) {
    
    queue <FrameWrap> queue;
    CameraProcessor camera(queue);


    camera.insertToQueue();

    ASSERT_EQ(2, dataFromCamera.size());  // We pushed one frame initially, now added one more

    // You would need to define the expected values based on your specific test case
    ASSERT_EQ(expectedFrameNumber, dataFromCamera.back().frameNumber);
    ASSERT_EQ(expectedTimestamp, dataFromCamera.back().timestamp);
    // Implement a suitable image comparison function or library
    ASSERT_TRUE(compareImages(expectedImage, dataFromCamera.back().image));
}



TEST(CurrentTimeTest, TestCurrentTime) {
    // Get the current system time using the C++ standard library
    auto now = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
    std::tm timeinfo;

    // Use thread-safe version of localtime
    localtime_s(&timeinfo, &timestamp);

    char buffer[28];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    // Calculate milliseconds
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));

    std::string expected_formatted_time = buffer;

    // Call the currentTime function to get the result
    std::string actual_formatted_time = currentTime();

    // Calculate the absolute difference in milliseconds
    int expected_milliseconds = std::stoi(expected_formatted_time.substr(20, 3));
    int actual_milliseconds = std::stoi(actual_formatted_time.substr(20, 3));
    int time_difference = std::abs(expected_milliseconds - actual_milliseconds);

    // Check if the time difference is less than 5 milliseconds
    ASSERT_LE(time_difference, 5);
}


TEST(YoloRectTest, CalculatesAveragePerChannel) {
    FrameWrap frw;
    SQLHandler sql;
    vector<Detection>det;
    vector<string>classL;

    RectHandler rh(frw, det, classL, sql);

    Mat testImage(2, 2, CV_8UC3);
    testImage.at<Vec3b>(0, 0) = Vec3b(10, 20, 30);
    testImage.at<Vec3b>(0, 1) = Vec3b(40, 50, 60);
    testImage.at<Vec3b>(1, 0) = Vec3b(70, 80, 90);
    testImage.at<Vec3b>(1, 1) = Vec3b(100, 110, 120);

    // Call the function
    float avgB, avgG, avgR;
    rh.calcAvgPerChannel(testImage, &avgB, &avgG, &avgR);

    // Check the results with a tolerance (e.g., due to floating-point precision)
    EXPECT_FLOAT_EQ(avgB, (10 + 40 + 70 + 100) / 4);
    EXPECT_FLOAT_EQ(avgG, (20 + 50 + 80 + 110) / 4);
    EXPECT_FLOAT_EQ(avgR, (30 + 60 + 90 + 120) / 4);
}

