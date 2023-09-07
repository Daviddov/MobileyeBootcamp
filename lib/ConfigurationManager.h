#pragma once
#include "../nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class ConfigurationManager {
private:
    json config;
    double cameraThreshold;
    int backendQueueSize;
    std::string cameraIP;
    int cameraPort;
    std::string backendIP;
    int backendPort;

public:
    ConfigurationManager();

    // Getter functions
    double getCameraThreshold() const {
        return cameraThreshold;
    }

    int getBackendQueueSize() const {
        return backendQueueSize;
    }

    std::string getCameraIP() const {
        return cameraIP;
    }

    int getCameraPort() const {
        return cameraPort;
    }

    std::string getBackendIP() const {
        return backendIP;
    }

    int getBackendPort() const {
        return backendPort;
    }

    bool saveConfigToFile(const std::string& filename);
    bool readConfigFromFile(const std::string& filename);

    void editConfig();

    // Setter functions
    void setCameraThreshold(double threshold) {
        cameraThreshold = threshold;
    }

    void setBackendQueueSize(int queueSize) {
        backendQueueSize = queueSize;
    }

    void setCameraIP(const std::string& ip) {
        cameraIP = ip;
    }

    void setCameraPort(int port) {
        cameraPort = port;
    }

    void setBackendIP(const std::string& ip) {
        backendIP = ip;
    }

    void setBackendPort(int port) {
        backendPort = port;
    }

    void editSingleConfigField();

    void printConfig();
};


void configRun();