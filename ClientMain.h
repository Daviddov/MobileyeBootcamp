#include "CameraProcessor.h"
#include "ConfigurationManager.h"

class ClientMain {
private:
    ConfigurationManager& configManager;  // Reference to the singleton instance
    CameraProcessor camera;

public:
    // Constructor now initializes the camera directly
    ClientMain() : configManager(ConfigurationManager::getInstance()), camera(
        configManager.getFieldValue<std::string>("videoPath"),
        configManager.getFieldValue<int>("numFrames"),
        configManager.getFieldValue<double>("cameraThreshold")
    ) {
        // log init
        LogPriority priority = InfoPriority;
        std::mutex logMutex;
        Logger::EnableFileOutput();

        Logger::Info("The camera process is started");

        if (!camera.capture.isOpened()) {
            Logger::Critical("Error opening video file");
            return;
        }

        camera.run();
        Logger::Info("The camera process is finished");
    }

    void menu() {
        int choice;
        do {
            std::cout << "Select a field to edit:" << std::endl;
            std::cout << "1. Start again" << std::endl;
            std::cout << "2. Change config" << std::endl;
            std::cout << "9. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1: {
                camera.run();
                break;
            }
            case 2: {
                configManager.editConfig();
                break;
            }
            case 9:
                // Exit the editing menu
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
            }
        } while (choice != 9);
    }
};
