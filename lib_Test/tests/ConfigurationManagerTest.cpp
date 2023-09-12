#include <gtest/gtest.h>
#include "ConfigurationManager.h"

// Define a fixture for ConfigurationManager tests
class ConfigurationManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary test file
        filename = "test_config.json";
    }

    void TearDown() override {
        // Clean up the test file
        remove(filename.c_str());
    }

    std::string filename;
};

TEST_F(ConfigurationManagerTest, SaveAndReadConfig) {
    // Create a ConfigurationManager instance
    ConfigurationManager manager(filename);

    // Save the default configuration to the file
    EXPECT_TRUE(manager.saveConfigToFile(filename));

    // Create a new ConfigurationManager instance to read from the file
    ConfigurationManager readManager(filename);
    EXPECT_TRUE(readManager.readConfigFromFile(filename));

    // Compare the configurations to ensure they match
    EXPECT_EQ(manager.getConfig(), readManager.getConfig());


    // Add new test cases for editSingleConfigField
    manager.editSingleConfigField("backendQueueSize", 200);
    EXPECT_EQ(manager.getConfig()["backendQueueSize"], 200);

    manager.editSingleConfigField("nonExistentField", 42);
    // Expecting no change because the field doesn't exist
    EXPECT_EQ(manager.getConfig()["nonExistentField"], nullptr);

}

TEST_F(ConfigurationManagerTest, EditConfig) {
    // Create a ConfigurationManager instance
    ConfigurationManager manager(filename);

    // Set up input stream for simulating user input
    std::istringstream input_stream("2\n100\n8\n");
    std::cin.rdbuf(input_stream.rdbuf()); // Redirect std::cin to input_stream

    // Edit the configuration (change Backend Queue Size)
    manager.editConfig();

    // Check if the configuration has been updated
    EXPECT_EQ(manager.getConfig()["backendQueueSize"], 100);
}

TEST_F(ConfigurationManagerTest, printConfig) {
    // Create a ConfigurationManager instance
    ConfigurationManager manager(filename);

    // Edit the configuration (change Backend Queue Size)
    manager.editSingleConfigField("backendQueueSize", 200);

    // Add new test cases for printConfig
    std::ostringstream output_stream;
    std::streambuf* cout_buffer = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf()); // Redirect std::cout to output_stream

    manager.printConfig();
    std::cout.rdbuf(cout_buffer); // Restore std::cout

    // Check if the output contains the expected configuration values
    std::string output = output_stream.str();
    EXPECT_NE(output.find("backendQueueSize: 200"), std::string::npos);
}
