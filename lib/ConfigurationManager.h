#pragma once
#include "../nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string> // Add this for string data type

using json = nlohmann::json;

class ConfigurationManager {
private:
    json config;

    void defaultConfiguration();
public:
    ConfigurationManager();
    ConfigurationManager(const std::string& filename);

    bool saveConfigToFile(const std::string& filename);
    bool readConfigFromFile(const std::string& filename);

    void editConfig();

    // Use specific data types for configuration fields
    void editSingleConfigField(const std::string& fieldName, double newValue); // Example for double values
    void editSingleConfigField(const std::string& fieldName, int newValue);    // Example for integer values
    void editSingleConfigField(const std::string& fieldName, const std::string& newValue); // Example for string values

    json getConfig() {
        return config;
    }

    // Implement the function template
    template <typename T>
    T getFieldValue(const std::string& fieldName) const {
        // Check if the field name exists in the configuration
        if (config.find(fieldName) != config.end()) {
            try {
                return config[fieldName].get<T>();
            }
            catch (const json::exception& e) {
                // Handle JSON parsing errors or type mismatch
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        // Handle the case where the field doesn't exist or type conversion fails
        return T(); // Return a default-constructed value for the type T
    }


    void printConfig();
};

void configRun();