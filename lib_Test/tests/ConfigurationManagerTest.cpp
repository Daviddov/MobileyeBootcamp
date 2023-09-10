#include <gtest/gtest.h>
#include "ConfigurationManager.h"

TEST(ConfigurationManagerTest, SaveAndReadConfig) {
    // Create a temporary test file
    const std::string filename = "test_config.json";

    // Create a ConfigurationManager instance
    ConfigurationManager manager;

    // Save the default configuration to the file
    EXPECT_TRUE(manager.saveConfigToFile(filename));

    // Create a new ConfigurationManager instance to read from the file
    ConfigurationManager readManager;
    EXPECT_TRUE(readManager.readConfigFromFile(filename));

    // Compare the configurations to ensure they match
    EXPECT_EQ(manager.getConfig(), readManager.getConfig());

    // Clean up the test file
    remove(filename.c_str());
}

TEST(ConfigurationManagerTest, EditConfig) {
    // Create a ConfigurationManager instance
    ConfigurationManager manager;

    // Set up input stream for simulating user input
    std::istringstream input_stream("2\n100\n8\n");
    std::cin.rdbuf(input_stream.rdbuf()); // Redirect std::cin to input_stream

    // Edit the configuration (change Backend Queue Size)
    manager.editConfig();

    // Check if the configuration has been updated
    EXPECT_EQ(manager.getConfig()["backendQueueSize"], 100);
}




