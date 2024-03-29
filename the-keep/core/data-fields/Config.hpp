/**
 * @filename: Config.hpp
 * @description: The declaration of the parser for the data field configuration file.
 * @author: KeepId
 * @date: February 19, 2022
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <jsoncpp/json/json.h>

using namespace std;

class Config{
    public:
        /**
         * Config::initialize()
         * @brief Intializes the configuration file. Read from the file
         *        specified in 'DATA_FIELD_CONFIG_FILE_NAME' of Constants.hpp.
         * @throw The configuration file does not follow the correct format.
         */
        static void initialize();

        /**
         * Config::uninitialize()
         * @brief Destroys the objects within the Config.
         * @throw Config was never initialized.
         */
        static void uninitialize();
        
        /**
         * Config::validateDecryptedDataFields()
         * @brief Validates that the data fields comply with the configuration constraints.
         * 
         * @param[in] data_fields The data fields Json object to validate.
         *                        Format: {"field1" : "value1", "field2" : "value2", ...}
         * 
         * @return A list of data fields that are considered to be invalid.
         */
        static vector<string> validateDecryptedDataFields(const Json::Value &data_fields);

        /**
         * Config::getOptionLists()
         * @brief A getter for the configuration option lists.
         * @return The Json object for the configuration option lists.
         */
        static Json::Value getOptionLists();

        /**
         * Config::getConstraints()
         * @brief A getter for the configuration data field constraints.
         * @return The Json object for the configuration data field constraints.
         */
        static Json::Value getConstraints();

    private:
        // Variables
        static inline bool initialized_ = false;
        static inline std::unique_ptr<Json::Value> data_field_config_;  // initializes with nullptr
};
