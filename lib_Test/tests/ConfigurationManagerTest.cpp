#include "ConfigurationManager.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(ConfigurationManager, SaveAndReadConfig) {
    ConfigurationManager configManager;

    // Save configuration to file
    ASSERT_TRUE(configManager.saveConfigToFile("test_config.json"));

    // Read configuration from the saved file
    ASSERT_TRUE(configManager.readConfigFromFile("test_config.json"));

    // Check if the configuration values were correctly read
    EXPECT_EQ(configManager.getCameraThreshold(), 0.9);
    EXPECT_EQ(configManager.getBackendQueueSize(), 5);
    EXPECT_EQ(configManager.getCameraIP(), "127.0.0.1");
    EXPECT_EQ(configManager.getCameraPort(), 8080);
    EXPECT_EQ(configManager.getBackendIP(), "127.0.0.1");
    EXPECT_EQ(configManager.getBackendPort(), 8000);
}

TEST(ConfigurationManager, EditSingleConfigField) {
    ConfigurationManager configManager;

    // Redirect cin and cout to stringstream to capture input and output
    std::stringstream input_stream;
    std::stringstream output_stream;
    std::streambuf* original_cin = std::cin.rdbuf(input_stream.rdbuf());
    std::streambuf* original_cout = std::cout.rdbuf(output_stream.rdbuf());

    // Simulate user input
    input_stream << "1\n"; // Choose Camera Threshold
    input_stream << "0.7\n"; // Enter new Camera Threshold

    // Call the function
    configManager.editSingleConfigField();

    // Restore cin and cout
    std::cin.rdbuf(original_cin);
    std::cout.rdbuf(original_cout);

    // Check if the cameraThreshold was updated
    EXPECT_EQ(configManager.getCameraThreshold(), 0.7);

    // Check the captured output for expected messages
    std::string expected_output =
        "Select the field to edit:\n"
        "1. Camera Threshold\n"
        "2. Backend Queue Size\n"
        "3. Camera IP\n"
        "4. Camera Port\n"
        "5. Backend IP\n"
        "6. Backend Port\n"
        "Enter your choice (1-6): "
        "Enter new Camera Threshold: ";

    EXPECT_EQ(output_stream.str(), expected_output);
}
