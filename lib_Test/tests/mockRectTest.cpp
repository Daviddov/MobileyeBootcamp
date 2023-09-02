//#include "../lib/SQLHandler.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
//#include "../lib/Rect.h"
//
//using namespace testing;

class JustForTest {
public:
    virtual int just() {
        int num = 5;
        int num2 = 5;
        return num + num2;
    }
};

class MockJustForTest : public JustForTest {
public:
    MOCK_METHOD(int, just, (), (override));
};


TEST(JustForTestMockTest, TestJustForTest) {
    MockJustForTest mockJustForTest;

    // Set up an expectation for the return value.
    EXPECT_CALL(mockJustForTest, just())
        .WillOnce(::testing::Return(100)); // Specify the expected return value
        
    // Call the method on the mock object
    int result = mockJustForTest.just();

    // Verify the result
    EXPECT_EQ(result, 100);
}


//class MockYoloRect : public SQLHandler {
//public:
//    MOCK_CONST_METHOD0(getValue, int());
//};
//
//TEST(YoloRectTest, TestGetValue) {
//    MockYoloRect mockYoloRect;
//
//    EXPECT_CALL(mockYoloRect, getValue())
//        .WillOnce(Return(100));
//
//    int result = mockYoloRect.getValue();
//    EXPECT_EQ(result, 100);
//}

//class MockMat {
//public:
//    MOCK_METHOD(uchar*, ptr, (int row), ());
//};
//
//class MockFrameWrap {
//    // Define mock methods and behavior here
//};
//
//class MockSQLHandler {
//    // Define mock methods and behavior here
//};



//class MockYoloRect : public YoloRect {
//public:
//        MOCK_METHOD4(calcAvgPerChannel, void(const cv::Mat& img, float* B, float* G, float* R));
//    
//};
//
//class YoloRectTest : public ::testing::Test {
//protected:
//    void SetUp() override {
//        // Set up any common resources or variables for your tests
//    }
//
//    void TearDown() override {
//        // Clean up any resources if needed
//        delete yoloRectUnderTest;
//    }
//    MockYoloRect* yoloRectUnderTest;
//};
//
//TEST_F(YoloRectTest, CalculatesAveragePerChannel) {
//    MockYoloRect mockYoloRect();
//    // Create a test image (you should replace this with a proper image)
//    cv::Mat testImage(2, 2, CV_8UC3);
//    testImage.at<cv::Vec3b>(0, 0) = cv::Vec3b(10, 20, 30);
//    testImage.at<cv::Vec3b>(0, 1) = cv::Vec3b(40, 50, 60);
//    testImage.at<cv::Vec3b>(1, 0) = cv::Vec3b(70, 80, 90);
//    testImage.at<cv::Vec3b>(1, 1) = cv::Vec3b(100, 110, 120);
//
//    float avgB, avgG, avgR;
//
//    EXPECT_CALL(*yoloRectUnderTest, calcAvgPerChannel(testImage, _, _, _))
//               .WillOnce(DoAll(SaveArg<1>(&avgB), SaveArg<2>(&avgG), SaveArg<3>(&avgR)));
//
//    yoloRectUnderTest->calcAvgPerChannel(testImage, &avgB, &avgG, &avgR);
//   
//    // Check the results with a tolerance (e.g., due to floating-point precision)
//    EXPECT_FLOAT_EQ(avgB, (10 + 40 + 70 + 100) / 4);
//    EXPECT_FLOAT_EQ(avgG, (20 + 50 + 80 + 110) / 4);
//    EXPECT_FLOAT_EQ(avgR, (30 + 60 + 90 + 120) / 4);
//}


//class MockYoloRect : public YoloRect {
//public:
//    MOCK_METHOD4(calcAvgPerChannel, void(const cv::Mat& img, float* B, float* G, float* R));
//};
//
//class YoloRectTest : public ::testing::Test {
//protected:
//    void SetUp() override {
//        // Set up any common resources or variables for your tests
//      //  yoloRectUnderTest = new MockYoloRect();
//    }
//
//    void TearDown() override {
//        // Clean up any resources if needed
//        delete yoloRectUnderTest;
//    }
//
//    MockYoloRect* yoloRectUnderTest;
//};

//TEST_F(YoloRectTest, CalculatesAveragePerChannel) {
//    // Create a test image (you should replace this with a proper image)
//    cv::Mat testImage(2, 2, CV_8UC3);
//    testImage.at<cv::Vec3b>(0, 0) = cv::Vec3b(10, 20, 30);
//    testImage.at<cv::Vec3b>(0, 1) = cv::Vec3b(40, 50, 60);
//    testImage.at<cv::Vec3b>(1, 0) = cv::Vec3b(70, 80, 90);
//    testImage.at<cv::Vec3b>(1, 1) = cv::Vec3b(100, 110, 120);
//
//    float avgB, avgG, avgR;
//
//    // Expect the mock function to be called and specify its behavior
//    EXPECT_CALL(*yoloRectUnderTest, calcAvgPerChannel(testImage, _, _, _))
//        .WillOnce(DoAll(SaveArg<1>(&avgB), SaveArg<2>(&avgG), SaveArg<3>(&avgR)));
//
//    // Call the function under test
//    yoloRectUnderTest->calcAvgPerChannel(testImage, &avgB, &avgG, &avgR);
//
//    // Check the results with a tolerance (e.g., due to floating-point precision)
//    EXPECT_FLOAT_EQ(avgB, (10 + 40 + 70 + 100) / 4);
//    EXPECT_FLOAT_EQ(avgG, (20 + 50 + 80 + 110) / 4);
//    EXPECT_FLOAT_EQ(avgR, (30 + 60 + 90 + 120) / 4);
//}


//class MockYoloRect : public YoloRect {
//public:
//    MOCK_METHOD4(calcAvgPerChannelMock, void(const cv::Mat& img, float* B, float* G, float* R));
//};
//
//class YoloRectTest : public ::testing::Test {
//protected:
//    void SetUp() override {
//       
//        // Set up any common resources or variables for your tests
//        yoloRectUnderTest = make_unique<MockYoloRect>();
//    }
//
//    void TearDown() override {
//        // Clean up any resources if needed
//    }
//
//     unique_ptr <MockYoloRect> yoloRectUnderTest;
//     
//};
//
//TEST_F(YoloRectTest, CalculatesAveragePerChannel) {
//    // Create a test image (you should replace this with a proper image)
//    cv::Mat testImage(2, 2, CV_8UC3);
//    testImage.at<Vec3b>(0, 0) = Vec3b(10, 20, 30);
//    testImage.at<Vec3b>(0, 1) = Vec3b(40, 50, 60);
//    testImage.at<Vec3b>(1, 0) = Vec3b(70, 80, 90);
//    testImage.at<Vec3b>(1, 1) = Vec3b(100, 110, 120);
//
//    float avgB, avgG, avgR;
//
//    // Expect the mock function to be called and specify its behavior
//    EXPECT_CALL(*yoloRectUnderTest, calcAvgPerChannelMock(testImage, _, _, _))
//        .WillOnce(DoAll(SaveArg<1>(&avgB), SaveArg<2>(&avgG), SaveArg<3>(&avgR)));
//
//    // Call the function under test
//    yoloRectUnderTest->calcAvgPerChannel(testImage, &avgB, &avgG, &avgR);
//
//    // Check the results with a tolerance (e.g., due to floating-point precision)
//    EXPECT_FLOAT_EQ(avgB, (10 + 40 + 70 + 100) / 4);
//    EXPECT_FLOAT_EQ(avgG, (20 + 50 + 80 + 110) / 4);
//    EXPECT_FLOAT_EQ(avgR, (30 + 60 + 90 + 120) / 4);
//}


//class YoloRect {
//public:
//    static void calcAvgPerChannel(const Mat& img, float* B, float* G, float* R) {
//        // Calculate the average per channel and assign to B, G, R pointers
//    }
//};

//class MockYoloRect : public YoloRect {
//public:
//
//    MOCK_METHOD(void, calcAvgPerChannel,(Mat& , float* , float* , float*));
//};
//
//class YoloRectTest : public ::testing::Test {
//protected:
//    void SetUp() override {
//        yoloRectUnderTest = std::make_unique<MockYoloRect>();
//    }
//
//    void TearDown() override {
//    }
//
//    std::unique_ptr<MockYoloRect> yoloRectUnderTest;
//};


//TEST_F(YoloRectTest, CalculatesAveragePerChannel) {
//    Mat testImage(2, 2, CV_8UC3);
//    testImage.at<Vec3b>(0, 0) = Vec3b(10, 20, 30);
//    testImage.at<Vec3b>(0, 1) = Vec3b(40, 50, 60);
//    testImage.at<Vec3b>(1, 0) = Vec3b(70, 80, 90);
//    testImage.at<Vec3b>(1, 1) = Vec3b(100, 110, 120);
//
//    float avgB, avgG, avgR;
//
//    // Expect the mock function to be called and specify its behavior
//    EXPECT_CALL(*yoloRectUnderTest, calcAvgPerChannel(testImage, _, _, _))
//        .WillOnce(DoAll(SaveArg<1>(&avgB), SaveArg<2>(&avgG), SaveArg<3>(&avgR)));
//
//    // Call the function under test
//    yoloRectUnderTest->calcAvgPerChannel(testImage, &avgB, &avgG, &avgR);
//
//    // Check the results with a tolerance (e.g., due to floating-point precision)
//    EXPECT_FLOAT_EQ(avgB, (10 + 40 + 70 + 100) / 4.0f);
//    EXPECT_FLOAT_EQ(avgG, (20 + 50 + 80 + 110) / 4.0f);
//    EXPECT_FLOAT_EQ(avgR, (30 + 60 + 90 + 120) / 4.0f);
//}