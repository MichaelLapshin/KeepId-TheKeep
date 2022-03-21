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
#include "../HelperFunctions.hpp"

using namespace std;

/**
 * Config::initialize()
 */
void Config::initialize(){
    if (Config::initialized_){
        throw runtime_error("Data field configurations were already initialized.");
    }

    // Reads all lines from the configurations file
    ifstream file_input_stream(DATA_FIELD_CONFIG_FILE_NAME);
    
    // Creates config Json object
    Json::CharReaderBuilder json_builder;
    string err_msg;
    Config::data_field_config_ = new Json::Value();
    bool parse_success = Json::parseFromStream(json_builder, file_input_stream, Config::data_field_config_, &err_msg);
    
    // Handles parsing errors
    if (!parse_success){
        throw runtime_error(
            "Error. The data field configuration file was unsuccessfully "
            "parsed.\n" + err_msg
        );
    }

    // Asserts the validity of the configurations
    Assertions::assertDataFieldConfig(*Config::data_field_config_);
    Config::initialized_ = true; 
}

/**
 * Config::deinitialize()
 */
void Config::uninitialize(){
    if (!Config::initialized_){
        throw runtime_error("Data field configurations were not initialized.");
    }

    delete Config::data_field_config_;
    Config::initialized_ = false; 
}

/**
 * Config::validateDecryptedDataFields()
 */
vector<string> Config::validateDecryptedDataFields(const Json::Value &data_fields){
    Assertions::assertValidDataFields(data_fields.getMemberNames());

    // Accumulates the invalid fields
    vector<string> invalid_fields;

    Json::Value option_lists = Config::getOptionsList();
    Json::Value constraints = Config::getConstraints();
    
    for (const string field : data_fields.getMemberNames()){
        // Options list check
        if (constraints[field][INPUT_TYPE].asString() == OPTIONS){
            string options = constraints[field][OPTIONS].asString();

            // Check if the option is within the options list
            bool is_valid_option = false;
            for(int i = 0; i < option_lists[options].size(); i++){
                if(data_fields[field].asString() == option_lists[options][i].asString()){
                    is_valid_option = true;
                    break;
                }
            }

            // If option is invalid, push-back to vector
            if (!is_valid_option){
                invalid_fields.push_back(field);
            }
        } 

        // Input string check
        else if (constraints[field][INPUT_TYPE].asString() == STRING ||
                 constraints[field][INPUT_TYPE].asString() == INTEGER){

            // Check against constraints
            bool is_valid_option = true;
            is_valid_option &= !data_fields[field].asString().empty();
            is_valid_option &= data_fields[field].asString().size() <= constraints[field][MAX_CHARS].asInt();
            
            // If the field must be an integer, then enforce that constraint
            if (constraints[field][INPUT_TYPE].asString() == INTEGER){
                bool all_int = true;
                for(const char &character : data_fields[field].asString()){
                    all_int &= isdigit(character);
                }
            }

            // If option is invalid, push-back to vector
            if (!is_valid_option){
                invalid_fields.push_back(field);
            }
        } else{
            invalid_fields.push_back(field);
        }
    }

    return invalid_fields;
}

/**
 * Config::getOptionsList()
 */
Json::Value Config::getOptionsList(){
    if (!Config::initialized_){
        throw runtime_error("Data field configurations were not initialized.");
    }
    return (*Config::data_field_config_)[OPTION_LISTS];
}

/**
 * Config::getConstraints()
 */
Json::Value Config::getConstraints(){
    if (!Config::initialized_){
        throw runtime_error("Data field configurations were not initialized.");
    }
    return (*Config::data_field_config_)[CONSTRAINTS];
}

