#pragma once
#include "../nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

struct Configuration {
    double cameraThreshold;
    int backendQueueSize;
    std::string cameraIP;
    int cameraPort;
    std::string backendIP;
    int backendPort;
};

class ConfigurationManeger {
public:
    

    json createDefaultConfigJson();

    bool saveConfigToFile(const std::string& filename, const Configuration& config);

    Configuration readConfigFromFile(const std::string& filename);

    void editConfig(Configuration& config);
};



void configRun();
