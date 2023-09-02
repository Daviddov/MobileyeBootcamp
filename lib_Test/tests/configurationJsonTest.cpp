#include "gtest/gtest.h"
#include "ConfigurationManager.h"


TEST(ConfigurationManagerTest, TestreadConfigFromFile) {
       
    ConfigurationManager manager;

    // Provide a sample JSON file with test configuration
    const std::string filename = "test_config.json";

    // Create the JSON content for the test file
    std::ofstream test_file(filename);
    test_file << R"({
        "cameraThreshold": 0.7,
        "backendQueueSize": 20,
        "cameraIP": "192.168.1.1",
        "cameraPort": 8888,
        "backendIP": "192.168.1.2",
        "backendPort": 9000
    })";
    test_file.close();

    Configuration config = manager.readConfigFromFile(filename);

    // Verify that the configuration values were read correctly
    EXPECT_EQ(config.cameraThreshold, 0.7);
    EXPECT_EQ(config.backendQueueSize, 20);
    EXPECT_EQ(config.cameraIP, "192.168.1.1");
    EXPECT_EQ(config.cameraPort, 8888);
    EXPECT_EQ(config.backendIP, "192.168.1.2");
    EXPECT_EQ(config.backendPort, 9000);
}

TEST(ConfigurationManagerTest, CreateDefaultConfigJsonTest) {
    ConfigurationManager manager;

    json defaultConfig = manager.createDefaultConfigJson();

    // Verify that the JSON object has the expected keys and values
    EXPECT_TRUE(defaultConfig.is_object());
    EXPECT_DOUBLE_EQ(defaultConfig["cameraThreshold"], 0.5);
    EXPECT_EQ(defaultConfig["backendQueueSize"], 10);
    EXPECT_EQ(defaultConfig["cameraIP"], "127.0.0.1");
    EXPECT_EQ(defaultConfig["cameraPort"], 8080);
    EXPECT_EQ(defaultConfig["backendIP"], "127.0.0.1");
    EXPECT_EQ(defaultConfig["backendPort"], 8000);
}

// Test case for ConfigurationManeger::saveConfigToFile function
TEST(ConfigurationManagerTest, SaveConfigToFileTest) {
    ConfigurationManager manager;

    // Create a sample Configuration object
    Configuration config;
    config.cameraThreshold = 0.7;
    config.backendQueueSize = 20;
    config.cameraIP = "192.168.1.1";
    config.cameraPort = 8888;
    config.backendIP = "192.168.1.2";
    config.backendPort = 9000;

    // Specify the test filename
    const std::string filename = "test_config_save.json";

    // Call the function to be tested
    bool result = manager.saveConfigToFile(filename, config);

    // Verify that the function returned true, indicating successful saving
    EXPECT_TRUE(result);

    // Read the saved JSON content from the file
    std::ifstream test_file(filename);
    std::string saved_content((std::istreambuf_iterator<char>(test_file)), std::istreambuf_iterator<char>());
    test_file.close();

    // Parse the JSON strings into JSON objects
    json parsed_saved = json::parse(saved_content);
    json parsed_expected = json::parse(R"({
        "cameraThreshold": 0.7,
        "backendQueueSize": 20,
        "cameraIP": "192.168.1.1",
        "cameraPort": 8888,
        "backendIP": "192.168.1.2",
        "backendPort": 9000
    })");

    // Verify that the parsed saved content matches the parsed expected content
    EXPECT_EQ(parsed_saved, parsed_expected);
}

// Define a test fixture to set up common resources for tests.
class EditConfigTest : public ::testing::Test {
protected:
    ConfigurationManager configManager;
    Configuration config;

    // This function is called before each test case.
    void SetUp() override {
        // Initialize a Configuration object with initial values.
        config.cameraThreshold = 50.0;
        config.backendQueueSize = 10;
        config.cameraIP = "127.0.0.1";
        config.cameraPort = 8080;
        config.backendIP = "127.0.0.1";
        config.backendPort = 8000;
    }
};

// Define a test case for editConfig.
TEST_F(EditConfigTest, EditConfiguration) {
    // Create a stringstream to simulate user input.
    std::stringstream user_input;
    user_input << "75.5\n20\nnew_camera_ip\n9091\nnew_backend_ip\n9092\n";

    // Redirect cin to the stringstream.
    std::cin.rdbuf(user_input.rdbuf());

    // Call the editConfig function.
    configManager.editConfig(config);

    // Verify that the configuration has been updated correctly.
    EXPECT_EQ(config.cameraThreshold, 75.5);
    EXPECT_EQ(config.backendQueueSize, 20);
    EXPECT_EQ(config.cameraIP, "new_camera_ip");
    EXPECT_EQ(config.cameraPort, 9091);
    EXPECT_EQ(config.backendIP, "new_backend_ip");
    EXPECT_EQ(config.backendPort, 9092);
}

