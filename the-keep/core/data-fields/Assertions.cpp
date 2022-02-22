/**
 * @filename: Assertions.cpp
 * @description: Defines the common assertions associated with data-fields.
 * @author: KeepId
 * @date: February 19, 2022
 */

#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

#include <jsoncpp/json/json.h>

#include "../HelperFunctions.cpp"
#include "Config.hpp"
#include "Constants.hpp"
#include "Assertions.hpp"

using namespace std;

/**
 * Assertions::assertDataFieldConfig()
 */
void Assertions::assertDataFieldConfig(Json::Value& data_field_config){
    // Asserts the options list
    if (!data_field_config.isMember(OPTIONS_LIST) || !data_field_config[OPTIONS_LIST].isObject())
        throw runtime_error("The options list member is missing in the configuration file.");

    Json::Value options_list = data_field_config[OPTIONS_LIST];
    vector<string> option_names = options_list.getMemberNames();
    for(string member : option_names){
        if (!options_list[member].isArray())
            throw runtime_error("The options list configuration member '" + member + "' is not an array.");
    }

    // Asserts the data fields constraints
    if (!data_field_config.isMember(CONSTRAINTS) || !data_field_config[CONSTRAINTS].isObject())
        throw runtime_error("The constraints member is missing in the configuration file.");
    
    Json::Value constraints = data_field_config[CONSTRAINTS];
    for(string member : constraints.getMemberNames()){
        if (!constraints[member].isObject())
            throw runtime_error("The data field configuration member '" + member + "' is not a Json object.");
        
        if (constraints[member].size() != 2)
            throw runtime_error("The data field configuration member '" + member + "' contains keys that should not be there.");        
        if ((constraints[member].isMember(INPUT_TYPE) && constraints[member].isMember(OPTIONS)) == false && 
            (constraints[member].isMember(INPUT_TYPE) && constraints[member].isMember(MAX_CHARS)) == false)
            throw runtime_error("The data field configuration member '" + member + "' does not map to a valid object.");        
        
        // Check validity of the input type
        string input_type = constraints[member][INPUT_TYPE].asString();
        if (input_type == STRING || input_type == INTEGER){
            if (!constraints[member].isMember(MAX_CHARS)){
                throw runtime_error("An data field string or integer input type does not have max-chars configuration.");
            }else if (!constraints[member][MAX_CHARS].isInt()){
                throw runtime_error("Data field configuration '" + member + "' does not have an integer max-chars.");
            }
        }else if (input_type == OPTIONS){
            if (!constraints[member].isMember(OPTIONS)){
                throw runtime_error("Options input type for data field configuration member '" + member + "' does not have options member.");
            }else if (!constraints[member][OPTIONS].isString()){
                throw runtime_error("Data field configuration '" + member + "' does not have an string option.");
            }else if (findVectorString(option_names, constraints[member][OPTIONS].asString()) == -1){
                throw runtime_error("Data field configuration '" + member + "' does not specify an existing option list.");
            }
        }else{
            assert(false); // Should never reach this line
        }
    }
}

/**
 * Assertions::assertValidDataRequest()
 */
void Assertions::assertValidDataRequest(Json::Value& data_request_input){
    // Checks that the basic members exist
    if (!data_request_input.isMember(USER_ID) || !data_request_input[USER_ID].isString())
        throw runtime_error("Data request is missing the user id.");
    
    if (!data_request_input.isMember(REQUEST_ID) || !data_request_input[REQUEST_ID].isString())
        throw runtime_error("Data request is missing the request id.");
    
    if (!data_request_input.isMember(PRIVATE_KEYS) || !data_request_input[PRIVATE_KEYS].isObject())
        throw runtime_error("Data request is missing the private keys.");
    
    // Asserts the input data field configuration constraints
    Json::Value private_keys = data_request_input[PRIVATE_KEYS];
    if (private_keys.empty()) throw runtime_error("The private keys member is empty.");    

    for (string member : private_keys.getMemberNames()){
        vector<string> valid_data_fields = Config::getConstraints().getMemberNames();
        if (findVectorString(valid_data_fields, constraints[member][OPTIONS].asString()) == -1)
            throw runtime_error("Private key data field '" + member + "' is not valid.");

        if (!private_keys[member].isString())
            throw runtime_error("Data request private key for data field'" + member + "' is not a string.")
    
    }
}
