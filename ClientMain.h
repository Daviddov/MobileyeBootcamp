#include "CameraProcessor.h"
#include "ConfigurationManager.h"

class ClientMain {
	ConfigurationManager configManager;
	CameraProcessor camera;
public:
	ClientMain() : configManager("config.json"), camera(configManager.getFieldValue<string>("videoPath"),
		configManager.getFieldValue<int>("numFrames"),
		configManager.getFieldValue<double>("cameraThreshold")) {

		//log init
		LogPriority priority = InfoPriority;
		mutex logMutex;
		Logger::EnableFileOutput();

		Logger::Info("the camera process is started");

		if (!camera.capture.isOpened()) {
			Logger::Critical("Error opening video file");
			return;
		}

		camera.run();
		Logger::Info("the camera process is finised");
	}

	void menu() {
		int choice;
		do {
			std::cout << "Select a field to edit:" << std::endl;
			std::cout << "1. start again" << std::endl;
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