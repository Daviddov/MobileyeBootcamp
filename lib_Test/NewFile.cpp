#include "../lib/SQLHandler.h"
#include <gtest/gtest.h>
#include "gmock/gmock.h"
​
using namespace testing;
​
class MockYoloRect : public SQLHandler {
public:
    MOCK_CONST_METHOD0(getValue, int());
};
​
TEST(YoloRectTest, TestGetValue) {
    MockYoloRect mockYoloRect;
    ​
        EXPECT_CALL(mockYoloRect, getValue())
        .WillOnce(Return(100));
    ​
        int result = mockYoloRect.getValue();
    EXPECT_EQ(result, 100);
}