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

#include "../HelperFunctions.cpp"
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
 * Config::validateDataFields()
 */
vector<string> Config::validateDataFields(const Json::Value &data_fields){
    const vector<string> invalid_fields;

    Json::Value options_list = Config::getOptionsList();
    Json::Value constraints = Config::getConstraints();
    
    for (const string field : data_field.getMemberNames()){
        // Options list check
        if (constraints[field][INPUT_TYPE].asString() == OPTIONS){
            
            // Checks that data_field is one of the options
            assert(findVectorString(options_list[]., data_fields[field]) != -1);

            assert();
        } 

        // Input string check
        else if (constraints[field][INPUT_TYPE].asString() == STRING){
            
        } 

        // Input integer check
        else if (constraints[field][INPUT_TYPE].asString() == INTEGER){

        } else{
            invalid_fields.push_back(field);
        }
    }

    return invalid_fields;
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

