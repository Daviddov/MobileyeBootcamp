#include <gtest/gtest.h>
#include "Yolo.h"
#include "Detection.h"
#include <opencv2/opencv.hpp>

// Define a fixture class for your tests
class Yolo5Test : public ::testing::Test {
protected:
    // Member variables you might need in your tests
    Yolo5 yolo;

    // Set up common configurations before each test
    void SetUp() override {
        // You can add any necessary setup code here
    }

    // Clean up after each test
    void TearDown() override {
        // You can add any necessary cleanup code here
    }
};

// Define a test case
TEST_F(Yolo5Test, DetectFunctionTest) {
    // You can create a FrameWrap object and set it as the current frame
    FrameWrap frame;
    // Set frame1 properties
    frame.frameNumber = 1;
    frame.timestamp = "2023-09-19 10:00:00";

    // Load an image into frame1 (you should replace this with your image loading logic)
    frame.image = cv::Mat(cv::Scalar(0, 3, 0));
    cv::imshow("output", frame.image);
 
        cv::imshow("output", frame.image);


   

    yolo.setFrame(frame);

    // Call the detect function
    yolo.detect();

    // You can now add your assertions to check the behavior of the detect function
    // For example, check if the output contains expected results based on a sample input
    const std::vector<Detection>& output = yolo.getOutput();
    ASSERT_FALSE(output.empty()); // Check if the output is not empty
    ASSERT_GT(output[0].confidence, 0.0f); // Check if the confidence score is greater than 0
    ASSERT_GE(output[0].class_id, 0); // Check if the class_id is non-negative
}