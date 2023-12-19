#pragma once
#include "json.hpp"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

class ConfigurationManager {
private:
    json config;

    void defaultConfiguration();
    ConfigurationManager();
    ConfigurationManager(const std::string& filename);


public:
    static ConfigurationManager& getInstance() {
        static ConfigurationManager configuration("config.json");
        return configuration;
    }

    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    bool saveConfigToFile(const std::string& filename);
    bool readConfigFromFile(const std::string& filename);

    void editConfig();

    void editSingleConfigField(const std::string& fieldName, double newValue);
    void editSingleConfigField(const std::string& fieldName, int newValue);
    void editSingleConfigField(const std::string& fieldName, const std::string& newValue);

    json getConfig() {
        return config;
    }

    template <typename T>
    T getFieldValue(const std::string& fieldName) const {
        if (config.find(fieldName) != config.end()) {
            try {
                return config[fieldName].get<T>();
            }
            catch (const json::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        return T();
    }

    void printConfig();
};


void configRun();
