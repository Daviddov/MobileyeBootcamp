#include "ConfigurationManager.h"
// Define a struct to hold configuration settings



 ConfigurationManager::ConfigurationManager(){
    config["cameraThreshold"] = 0.9;
    config["backendQueueSize"] = 5;
    config["cameraIP"] = "127.0.0.1";
    config["cameraPort"] = 8080;
    config["backendIP"] = "127.0.0.1";
    config["backendPort"] = 8000;
}

bool ConfigurationManager::saveConfigToFile(const std::string& filename){
    std::ofstream output_file(filename);
    if (output_file.is_open()) {
        output_file << config.dump(4);
        output_file.close();
        return true;
    }
    return false;
}

bool ConfigurationManager::readConfigFromFile(const std::string& filename) {

    std::ifstream input_file(filename);
    if (input_file.is_open()) {
        input_file >> config;

        cameraThreshold = config.value("cameraThreshold", 0.5);
        backendQueueSize = config.value("backendQueueSize", 10);
        cameraIP = config.value("cameraIP", "127.0.0.1");
        cameraPort = config.value("cameraPort", 8080);
        backendIP = config.value("backendIP", "127.0.0.1");
        backendPort = config.value("backendPort", 8000);
    return true;
    }

    return false;
}

void ConfigurationManager::editConfig() {
    std::cout << "Enter new Camera Threshold: ";
    std::cin >> cameraThreshold;

    std::cout << "Enter new Backend Queue Size: ";
    std::cin >> backendQueueSize;

    std::cout << "Enter new Camera IP: ";
    std::cin >> cameraIP;

    std::cout << "Enter new Camera Port: ";
    std::cin >> cameraPort;

    std::cout << "Enter new Backend IP: ";
    std::cin >> backendIP;

    std::cout << "Enter new Backend Port: ";
    std::cin >> backendPort;
}
void ConfigurationManager::editSingleConfigField() {
    int choice;
    std::cout << "Select the field to edit:" << std::endl;
    std::cout << "1. Camera Threshold" << std::endl;
    std::cout << "2. Backend Queue Size" << std::endl;
    std::cout << "3. Camera IP" << std::endl;
    std::cout << "4. Camera Port" << std::endl;
    std::cout << "5. Backend IP" << std::endl;
    std::cout << "6. Backend Port" << std::endl;
    std::cout << "Enter your choice (1-6): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << "Enter new Camera Threshold: ";
        std::cin >> cameraThreshold;
        break;
    case 2:
        std::cout << "Enter new Backend Queue Size: ";
        std::cin >> backendQueueSize;
        break;
    case 3:
        std::cout << "Enter new Camera IP: ";
        std::cin >> cameraIP;
        break;
    case 4:
        std::cout << "Enter new Camera Port: ";
        std::cin >> cameraPort;
        break;
    case 5:
        std::cout << "Enter new Backend IP: ";
        std::cin >> backendIP;
        break;
    case 6:
        std::cout << "Enter new Backend Port: ";
        std::cin >> backendPort;
        break;
    default:
        std::cout << "Invalid choice." << std::endl;
        break;
    }
}

void ConfigurationManager::printConfig() {
    std::cout << "Current Configuration:" << std::endl;
    std::cout << "Camera Threshold: " << cameraThreshold << std::endl;
    std::cout << "Backend Queue Size: " << backendQueueSize << std::endl;
    std::cout << "Camera IP: " << cameraIP << " Port: " << cameraPort << std::endl;
    std::cout << "Backend IP: " << backendIP << " Port: " << backendPort << std::endl;

}

void configRun() {
    ConfigurationManager j;
    j.saveConfigToFile("config.json");
    j.readConfigFromFile("config.json");
    j.printConfig();
    j.editConfig();
    j.printConfig();

    j.editSingleConfigField();
    j.printConfig();
}