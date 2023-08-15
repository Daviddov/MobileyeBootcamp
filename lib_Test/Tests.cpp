#include "../lib/Header.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"



TEST(TestCaseName, TestName) {

	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(CalcAvgPerChanelTest, TestCalcAvgPerChanel) {

    Mat testImage(3, 3, CV_8UC3);
    testImage.setTo(Scalar(100, 150, 200));

    float B=0, G=0, R =0 ;
    calcAvgPerChanel(testImage, &B, &G, &R);

    //// Add your expected 
    float expectedB = 100.0f;
    float expectedG = 150.0f;
    float expectedR = 200.0f;

    // Check the results 
    EXPECT_EQ(expectedB, B);
    EXPECT_EQ(expectedG, G);
    EXPECT_EQ(expectedR, R);
}

TEST(CalcAbsDiffTest, TestCalcAbsDiff) {

    Mat testImage1(3, 3, CV_8UC3, Scalar(100, 150, 200));
    Mat testImage2(3, 3, CV_8UC3, Scalar(100, 150, 200));


    ASSERT_FALSE(calcAbsDiff(testImage1, testImage2));


    Mat testImage3(3, 3, CV_8UC3, Scalar(100, 150, 200));
    Mat testImage4(3, 3, CV_8UC3, Scalar(110, 160, 210));


    ASSERT_TRUE(calcAbsDiff(testImage3, testImage4));
}

TEST(CurrentTimeTest, TestCurrentTime) {
    // Get the current system time using the C++ standard library
    auto now = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
    std::tm timeinfo;
    localtime_s(&timeinfo, &timestamp);

    char buffer[28];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));

    std::string expected_formatted_time = buffer;

    // Call the currentTime function to get the result
    std::string actual_formatted_time = currentTime();
    cout << (expected_formatted_time[expected_formatted_time.length() - 1] - actual_formatted_time[actual_formatted_time.length() - 1]) << endl;
    // Check if the result matches the expected formatted time
    ASSERT_EQ(expected_formatted_time, actual_formatted_time);
}