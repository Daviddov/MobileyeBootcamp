#include <gtest/gtest.h>
#include "QueueSafe.h"  // Include the header file for your Queue class
#include "CameraProcessor.h" 

using namespace cv;

class QueueTest : public ::testing::Test {
protected:
    QueueSafe<FrameWrap> queue;
    FrameWrap frameWarp1;
    FrameWrap frameWarp2;

    void SetUp() override {
        // Initialize FrameWrap objects for testing
        frameWarp1.image = Mat(Scalar(0, 9, 0));
        frameWarp1.timestamp = currentTime();
        frameWarp1.frameNumber = 1;

        frameWarp2.image = Mat(Scalar(9, 9, 0));
        frameWarp2.timestamp = currentTime();
        frameWarp2.frameNumber = 2;
    }
};

// Test case for Queue::push
TEST_F(QueueTest, PushTest) {
    // Push frameWarp1 to the queue
    queue.push(frameWarp1);

    // Check that the queue is not empty after pushing
    ASSERT_FALSE(queue.empty());

    // Check that the front element of the queue is frameWarp1
    ASSERT_EQ(queue.front(), frameWarp1);
}

// Test case for Queue::pop
TEST_F(QueueTest, PopTest) {
    // Push frameWarp1 to the queue
    queue.push(frameWarp1);

    // Pop an element from the queue
    queue.pop();

    // Check that the queue is empty after popping
    ASSERT_TRUE(queue.empty());
}

// Test case for Queue::front
TEST_F(QueueTest, FrontTest) {
    // Push frameWarp1 to the queue
    queue.push(frameWarp1);

    // Check that the front element of the queue is frameWarp1
    ASSERT_EQ(queue.front(), frameWarp1);
}

// Test case for Queue::empty
TEST_F(QueueTest, EmptyTest) {
    // Check that the queue is initially empty
    ASSERT_TRUE(queue.empty());

    // Push frameWarp1 to the queue
    queue.push(frameWarp1);

    // Check that the queue is not empty after pushing
    ASSERT_FALSE(queue.empty());
}

// Test case for Queue::size
TEST_F(QueueTest, SizeTest) {
    // Check that the queue size is initially 0
    ASSERT_EQ(queue.size(), 0);

    // Push two items to the queue
    queue.push(frameWarp1);
    queue.push(frameWarp2);

    // Check that the queue size is 2 after pushing
    ASSERT_EQ(queue.size(), 2);
}

// Test case for pushing more elements than the queue capacity
TEST_F(QueueTest, PushOverflowTest) {
    // Push 6 FrameWrap objects to the queue
    for (int i = 0; i < 6; ++i) {
        FrameWrap frame;
        frame.image = Mat(Scalar(i, 9, 0));
        frame.timestamp = currentTime();
        frame.frameNumber = i + 1;
        queue.push(frame);
    }

    // Check that the queue size is equal to its capacity (5)
    ASSERT_EQ(queue.size(), QUEUE_SIZE);

}