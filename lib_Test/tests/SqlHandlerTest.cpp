#include "../lib/Header.h"
#include "../lib/Camera.h"
#include "../lib/RectHandler.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"
#include "functionForTests.h"






TEST(SqlHandlerTest,  checkIfDataCorrect) {
    
    SQLHandler sql;
    int id = 1;
    SentToDataBase sentToDb;
   
    GetFromDataBase getDb;
    createFakeFrameWrapForTest(sentToDb);
    createFakeRectForTest(sentToDb);
    string test;
    
   bool isCreate = sql.createTableIfNotExists();
   bool isWrite = sql.insertData(sentToDb.rect, sentToDb.fw, sentToDb.objTipe , sentToDb.r, sentToDb.g, sentToDb.b);

    sql.getRow(id,getDb);


    EXPECT_TRUE(isCreate);
    EXPECT_TRUE(isWrite);
    EXPECT_FLOAT_EQ(sentToDb.r,getDb.r);
    EXPECT_FLOAT_EQ(sentToDb.g, getDb.g);
    EXPECT_FLOAT_EQ(sentToDb.b, getDb.b);
    EXPECT_EQ(id, getDb.id);
    EXPECT_EQ(sentToDb.rect.width, getDb.rect.width);
    EXPECT_EQ(sentToDb.rect.height, getDb.rect.height);
    EXPECT_EQ(sentToDb.rect.x, getDb.rect.x);
    EXPECT_EQ(sentToDb.rect.y, getDb.rect.y);
    EXPECT_EQ(sentToDb.fw.frameNumber, getDb.fw.frameNumber);
    EXPECT_EQ(sentToDb.objTipe, getDb.typeObject);


}

//Do not open this test Aharon needs to finish it

//TEST(InsertToQueueTest, BasicFunctionality) {
    
//    string path = R"(./assets/forTest.mp4)";
//    int id = 400;
//    queue <FrameWrap> queue;
//    CameraProcessor camera(queue,id,path);
//
//
//    camera.insertToQueue();
//
//    ASSERT_EQ(2, dataFromCamera.size());  // We pushed one frame initially, now added one more
//
//    // You would need to define the expected values based on your specific test case
//    ASSERT_EQ(expectedFrameNumber, dataFromCamera.back().frameNumber);
//    ASSERT_EQ(expectedTimestamp, dataFromCamera.back().timestamp);
//    // Implement a suitable image comparison function or library
//    ASSERT_TRUE(compareImages(expectedImage, dataFromCamera.back().image));
//}