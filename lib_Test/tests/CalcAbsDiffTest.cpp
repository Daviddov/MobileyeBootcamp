#include "../lib/Header.h"
#include "../lib/Camera.h"
#include "../lib/RectHandler.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"
#include "functionForTests.h"





//TEST(CalcAbsDiffTest, TestCalcAbsDiff) {
//
//    Mat testImage1(3, 3, CV_8UC3, Scalar(100, 150, 200));
//    Mat testImage2(3, 3, CV_8UC3, Scalar(100, 150, 200));
//
//    Queue<FrameWrap> queue;
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
//    camera.setFrame(testImage3);
//    camera.setPrev(testImage4);
//
//    ASSERT_TRUE(camera.calcAbsDiff());
//}

