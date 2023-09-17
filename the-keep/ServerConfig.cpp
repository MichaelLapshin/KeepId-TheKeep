/**
 * @filename: ServerConfig.hpp
 * @description: The implementation for the parser for the data field configuration file.
 * @author: KeepId, IL
 * @date: November 18, 2022
 */

#include <string>
#include <fstream>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>

#include "ServerConfig.hpp"
#include "core/data-fields/Constants.hpp"  // for MAIN_CONFIG_FILE_NAME; TODO: may need to be moved

/**
 * Config::initialize()
 */
void ServerConfig::initialize(){
//  Todo: 
// 1) define key configs; maybe a map - K-V pairs
// 2) defaults can be in code; soft config - a file

/*    
    if (Config::initialized_){
        throw runtime_error("Data field configuration was already initialized.");
    }

    // Reads all lines from the configurations file
    ifstream file_input_stream(DATA_FIELD_CONFIG_FILE_NAME);
    
    // Creates config Json object
    Json::CharReaderBuilder json_builder;
    string err_msg;
    ServerConfig::data_field_config_ = make_unique<Json::Value>(Json::Value());
    bool parse_success = Json::parseFromStream(json_builder, file_input_stream, Config::data_field_config_.get(), &err_msg);
    
    // Handles parsing errors
    if (!parse_success){
        throw runtime_error(
            "Error. The data field configuration file was unsuccessfully parsed.\n" + err_msg
        );
    }
*/
    // Asserts the validity of the configurations
    // Assertions::assertDataFieldConfig(*Config::data_field_config_);
    // Config::initialized_ = true; 
}