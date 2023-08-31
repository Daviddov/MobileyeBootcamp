
#include "RectHandler.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"


TEST(RectHandlerTest, CalculatesAveragePerChannel) {

    FrameWrap frw;
    SQLHandler sql;
    vector<Detection>det;
    vector<string>classL;

    RectHandler recthandler(frw, det, classL, sql);

    Mat testImage(2, 2, CV_8UC3);
    testImage.at<Vec3b>(0, 0) = Vec3b(10, 20, 30);
    testImage.at<Vec3b>(0, 1) = Vec3b(40, 50, 60);
    testImage.at<Vec3b>(1, 0) = Vec3b(70, 80, 90);
    testImage.at<Vec3b>(1, 1) = Vec3b(100, 110, 120);

    // Call the function
    float avgB, avgG, avgR;
    recthandler.calcAvgPerChannel(testImage, &avgB, &avgG, &avgR);

    // Check the results with a tolerance (e.g., due to floating-point precision)
    EXPECT_FLOAT_EQ(avgB, (10 + 40 + 70 + 100) / 4);
    EXPECT_FLOAT_EQ(avgG, (20 + 50 + 80 + 110) / 4);
    EXPECT_FLOAT_EQ(avgR, (30 + 60 + 90 + 120) / 4);
}

