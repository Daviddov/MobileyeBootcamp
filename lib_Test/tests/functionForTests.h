#pragma once
#include "../../lib/Header.h"
#include "../../lib/CameraProcessor.h"
#include "../../lib/RectHandler.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../../sqlite3/sqlite3.h"

struct SentToDataBase {

    Rect rect;
    FrameWrap fw;
    string objTipe = "car";
    float r = 3.8;
    float g = 4.0;
    float b = 3.9;
};

void createFakeFrameWrapForTest(SentToDataBase& toDb);
void createFakeRectForTest(SentToDataBase& toDb);
//float stringToFloat(const string& str);
