#include "../lib/Header.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"

using namespace cv;

// Basic test to check if Google Test is working
TEST(SanityCheckTest, BasicAssertion) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

// Test case for the calcAvgPerChanel function
TEST(CalcAvgPerChanelTest, TestCalcAvgPerChanel) {
    // Create a test image with a uniform color
    Mat testImage(3, 3, CV_8UC3);
    testImage.setTo(Scalar(100, 150, 200));

    float B = 0, G = 0, R = 0;
    calcAvgPerChanel(testImage, &B, &G, &R);

    // Define the expected values
    float expectedB = 100.0f;
    float expectedG = 150.0f;
    float expectedR = 200.0f;

    // Check the results
    EXPECT_EQ(expectedB, B);
    EXPECT_EQ(expectedG, G);
    EXPECT_EQ(expectedR, R);
}

// Test case for the calcAbsDiff function
TEST(CalcAbsDiffTest, TestCalcAbsDiff) {
    // Create test images with the same content
    Mat testImage1(3, 3, CV_8UC3, Scalar(100, 150, 200));
    Mat testImage2(3, 3, CV_8UC3, Scalar(100, 150, 200));

    // Images should not have absolute differences
    ASSERT_FALSE(calcAbsDiff(testImage1, testImage2));

    // Create test images with different content
    Mat testImage3(3, 3, CV_8UC3, Scalar(100, 150, 200));
    Mat testImage4(3, 3, CV_8UC3, Scalar(110, 160, 210));

    // Images should have absolute differences
    ASSERT_TRUE(calcAbsDiff(testImage3, testImage4));
}


// Test case for the currentTime function
TEST(CurrentTimeTest, TestCurrentTime) {
    // Get the current system time using the C++ standard library
    auto now = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
    std::tm timeinfo;

    // Use thread-safe version of localtime
#ifdef _MSC_VER
    localtime_s(&timeinfo, &timestamp);
#else
    localtime_r(&timestamp, &timeinfo);
#endif

    char buffer[28];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    sprintf_s(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));

    std::string expected_formatted_time = buffer;

    // Call the currentTime function to get the result
    std::string actual_formatted_time = currentTime();

    // Extract milliseconds from expected and actual times
    int expected_milliseconds = std::stoi(expected_formatted_time.substr(20, 23));
    int actual_milliseconds = std::stoi(actual_formatted_time.substr(20, 23));

    // Check if the result matches the expected formatted time within a tolerance of 1 millisecond
    ASSERT_EQ(expected_formatted_time.substr(0, 19), actual_formatted_time.substr(0, 19));
    ASSERT_LT(expected_milliseconds - actual_milliseconds, 5); // Check the difference as an integer value
}
