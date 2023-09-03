#include "functionForTests.h"
using namespace cv;

void createFakeFrameWrapForTest(SentToDataBase& toDb) {
 toDb.fw.timestamp = currentTime();
    toDb.fw.frameNumber = 1;
}

void createFakeRectForTest(SentToDataBase& toDb){
  toDb.rect.height = 252;
    toDb.rect.width = 234;
    toDb.rect.y = 756;
    toDb.rect.x = 1043;
}

//float stringToFloat(const string& str) {
//    try {
//        return stof(str);
//    }
//    catch (const std::exception& e) {
//       cerr << "Error converting string to float: " << e.what() << endl;
//        return 0.0f; // Default value in case of error
//    }
//}