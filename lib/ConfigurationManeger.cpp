#include "ConfigurationManeger.h"
// Define a struct to hold configuration settings



json ConfigurationManeger::createDefaultConfigJson() {
    json config;
    config["cameraThreshold"] = 0.5;
    config["backendQueueSize"] = 10;
    config["cameraIP"] = "127.0.0.1";
    config["cameraPort"] = 8080;
    config["backendIP"] = "127.0.0.1";
    config["backendPort"] = 8000;
    return config;
}

bool ConfigurationManeger::saveConfigToFile(const std::string& filename, const Configuration& config) {
    json config_json;
    config_json["cameraThreshold"] = config.cameraThreshold;
    config_json["backendQueueSize"] = config.backendQueueSize;
    config_json["cameraIP"] = config.cameraIP;
    config_json["cameraPort"] = config.cameraPort;
    config_json["backendIP"] = config.backendIP;
    config_json["backendPort"] = config.backendPort;

    std::ofstream output_file(filename);
    if (output_file.is_open()) {
        output_file << config_json.dump(4);
        output_file.close();
        return true;
    }
    return false;
}

Configuration ConfigurationManeger::readConfigFromFile(const std::string& filename) {
    Configuration config;
    json config_json;

    std::ifstream input_file(filename);
    if (input_file.is_open()) {
        input_file >> config_json;

        config.cameraThreshold = config_json.value("cameraThreshold", 0.5);
        config.backendQueueSize = config_json.value("backendQueueSize", 10);
        config.cameraIP = config_json.value("cameraIP", "127.0.0.1");
        config.cameraPort = config_json.value("cameraPort", 8080);
        config.backendIP = config_json.value("backendIP", "127.0.0.1");
        config.backendPort = config_json.value("backendPort", 8000);
    }

    return config;
}

void ConfigurationManeger::editConfig(Configuration& config) {
    std::cout << "Enter new Camera Threshold: ";
    std::cin >> config.cameraThreshold;

    std::cout << "Enter new Backend Queue Size: ";
    std::cin >> config.backendQueueSize;

    std::cout << "Enter new Camera IP: ";
    std::cin >> config.cameraIP;

    std::cout << "Enter new Camera Port: ";
    std::cin >> config.cameraPort;

    std::cout << "Enter new Backend IP: ";
    std::cin >> config.backendIP;

    std::cout << "Enter new Backend Port: ";
    std::cin >> config.backendPort;
}

void configRun() {
    ConfigurationManeger j;

    Configuration config = j.readConfigFromFile("config.json");

    std::cout << "Current Configuration:" << std::endl;
    std::cout << "Camera Threshold: " << config.cameraThreshold << std::endl;
    std::cout << "Backend Queue Size: " << config.backendQueueSize << std::endl;
    std::cout << "Camera IP: " << config.cameraIP << " Port: " << config.cameraPort << std::endl;
    std::cout << "Backend IP: " << config.backendIP << " Port: " << config.backendPort << std::endl;

    j.editConfig(config);

    if (j.saveConfigToFile("config.json", config)) {
        std::cout << "Configuration saved to 'config.json'" << std::endl;
    }
    else {
        std::cerr << "Unable to save configuration to file" << std::endl;
    }
}