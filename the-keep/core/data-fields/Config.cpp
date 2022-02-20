/**
 * @filename: Config.cpp
 * @description: The definition of the parser for the data field configuration file.
 * @author: KeepId
 * @date: February 19, 2022
 */

#include <string>
#include <fstream>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>

#include "Config.hpp"
#include "Constants.hpp"
#include "Assertions.hpp"

/**
 * Config::initialize()
 */
void Config::initialize(){
    if (Config::initialized){
        throw runtime_error("Data field configurations were already initialized.");
    }

    // Reads all lines from the configurations file
    std::ifstream file_input_stream(DATA_FIELD_CONFIG_FILE_NAME);
    std::string json_contents;
    json_contents.assign((std::istreambuf_iterator<char>(file_input_stream)),
                         (std::istreambuf_iterator<char>()));
    file_input_stream.close();
    
    // Creates config Json object
    Json::Reader file_reader;
    file_reader.parse(json_contents,
                      *Config::data_field_config,
                      false /* collectComments */);

    // Handles parsing errors
    if (!file_reader.getFormatedErrorMessages().empty()){
        throw runtime_error(
            "Error. The data field configuration file was unsuccessfully "
            "parsed.\n" + file_reader.getFormattedErrorMessages()
        );
    }

    // Asserts the validity of the configurations
    Assertions::assertDataFieldConfig(*Config::data_field_config);
    Config::initialized = true; 
}

/**
 * Config::deinitialize()
 */
void Config::deinitialize(){
    if (!Config::initialized){
        throw runtime_error("Data field configurations were not initialized.");
    }

    delete data_field_config;
    Config::initialized = false; 
}


/**
 * Config::getOptionsList()
 */
Json::Value Config::getOptionsList(){
    if (!Config::initialized){
        throw runtime_error("Data field configurations were not initialized.");
    }
    return (*data_field_config)[OPTIONS_LIST];
}

/**
 * Config::getConstraints()
 */
Json::Value Config::getConstraints(){
    if (!Config::initialized){
        throw runtime_error("Data field configurations were not initialized.");
    }
    return (*data_field_config)[CONSTRAINTS];
}

