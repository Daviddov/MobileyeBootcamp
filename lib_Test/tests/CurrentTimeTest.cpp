#include "../lib/Header.h"
#include "../lib/Camera.h"
#include "../lib/RectHandler.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"
#include "../sqlite3/sqlite3.h"
#include "functionForTests.h"





TEST(CurrentTimeTest, TestCurrentTime) {
    // Get the current system time using the C++ standard library
    auto now = chrono::system_clock::now();
    time_t timestamp = chrono::system_clock::to_time_t(now);
    tm timeinfo;

    // Use thread-safe version of localtime
#ifdef _WIN32
    localtime_s(&timeinfo, &timestamp);
#else
    localtime_r(&timestamp, &timeinfo);
#endif
    char buffer[28];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);

    // Calculate milliseconds
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), ":%03d", static_cast<int>(milliseconds));

    string expected_formatted_time = buffer;

    // Call the currentTime function to get the result
    string actual_formatted_time = currentTime();

    // Calculate the absolute difference in milliseconds
    int expected_milliseconds = stoi(expected_formatted_time.substr(20, 3));
    int actual_milliseconds = stoi(actual_formatted_time.substr(20, 3));
    int time_difference = abs(expected_milliseconds - actual_milliseconds);

    // Check if the time difference is less than 5 milliseconds
    ASSERT_LE(time_difference, 5);
}

