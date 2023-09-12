#include "ConfigurationManager.h" // Include your header file

ConfigurationManager::ConfigurationManager(const std::string& filename) {
    // Initialize default configuration values
    //if (!readConfigFromFile(filename)) 
    {

    defaultConfiguration();
    saveConfigToFile(filename);
    }
}
void ConfigurationManager::defaultConfiguration() {
    config["cameraThreshold"] = 0.9;
    config["backendQueueSize"] = 5;
    config["cameraIP"] = "0.0.0.0";
    config["cameraPort"] = "50051";
    //config["backendIP"] = "192.168.8.101";
    config["backendIP"] = "192.168.8.100";
    config["backendPort"] = "50051";
    config["numFrames"] = 30;
}

bool ConfigurationManager::saveConfigToFile(const std::string& filename) {
    std::ofstream output_file(filename);
    if (output_file.is_open()) {
        output_file << config.dump(4);
        output_file.close();
        return true;
    }
    return false;
}

bool ConfigurationManager::readConfigFromFile(const std::string& filename) {
    // Clear existing configuration before reading from the file
    config.clear();

    std::ifstream input_file(filename);
    if (input_file.is_open()) {
        try {
            input_file >> config;
            return true;
        }
        catch (const std::exception& e) {
            // Handle JSON parsing errors
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            return false;
        }
    }
    else {
        // Handle file open error
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
}

void ConfigurationManager::editConfig() {
    // Provide a menu to the user to select which fields to edit
    int choice;
    do {
        std::cout << "Select a field to edit:" << std::endl;
        std::cout << "1. Camera Threshold" << std::endl;
        std::cout << "2. Backend Queue Size" << std::endl;
        std::cout << "3. Camera IP" << std::endl;
        std::cout << "4. Camera Port" << std::endl;
        std::cout << "5. Backend IP" << std::endl;
        std::cout << "6. Backend Port" << std::endl;
        std::cout << "7. Number of Frames" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            double threshold;
            std::cout << "Enter new Camera Threshold: ";
            std::cin >> threshold;
            editSingleConfigField("cameraThreshold", threshold);
            break;
        }
        case 2: {
            int queueSize;
            std::cout << "Enter new Backend Queue Size: ";
            std::cin >> queueSize;
            editSingleConfigField("backendQueueSize", queueSize);
            break;
        }
        case 3: {
            std::string cameraIP;
            std::cout << "Enter new Camera IP: ";
            std::cin.ignore();
            std::getline(std::cin, cameraIP);
            editSingleConfigField("cameraIP", cameraIP);
            break;
        }
        case 4: {
            int cameraPort;
            std::cout << "Enter new Camera Port: ";
            std::cin >> cameraPort;
            editSingleConfigField("cameraPort", cameraPort);
            break;
        }
        case 5: {
            std::string backendIP;
            std::cout << "Enter new Backend IP: ";
            std::cin.ignore();
            std::getline(std::cin, backendIP);
            editSingleConfigField("backendIP", backendIP);
            break;
        }
        case 6: {
            int backendPort;
            std::cout << "Enter new Backend Port: ";
            std::cin >> backendPort;
            editSingleConfigField("backendPort", backendPort);
            break;
        }
        case 7: {
            int numFrames;
            std::cout << "Enter new Number of Frames: ";
            std::cin >> numFrames;
            editSingleConfigField("numFrames", numFrames);
            break;
        }
        case 8:
            // Exit the editing menu
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    } while (choice != 8);
}

void ConfigurationManager::editSingleConfigField(const std::string& fieldName, double newValue) {
    // Check if the field name exists in the configuration
    if (config.find(fieldName) != config.end()) {
        config[fieldName] = newValue;
    }
    else {
        std::cerr << "Field " << fieldName << " does not exist in the configuration." << std::endl;
    }
}

void ConfigurationManager::editSingleConfigField(const std::string& fieldName, int newValue) {
    // Check if the field name exists in the configuration
    if (config.find(fieldName) != config.end()) {
        config[fieldName] = newValue;
    }
    else {
        std::cerr << "Field " << fieldName << " does not exist in the configuration." << std::endl;
    }
}

void ConfigurationManager::editSingleConfigField(const std::string& fieldName, const std::string& newValue) {
    // Check if the field name exists in the configuration
    if (config.find(fieldName) != config.end()) {
        config[fieldName] = newValue;
    }
    else {
        std::cerr << "Field " << fieldName << " does not exist in the configuration." << std::endl;
    }
}




void ConfigurationManager::printConfig() {
    std::cout << "Current Configuration:" << std::endl;
    for (json::iterator it = config.begin(); it != config.end(); ++it) {
        // Access the key (field name) using it.key() and the value using it.value()
        std::cout << it.key() << ": " << it.value() << std::endl;
    }
}


