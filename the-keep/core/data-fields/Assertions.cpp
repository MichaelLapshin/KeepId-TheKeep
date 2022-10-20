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

#include "Assertions.hpp"
#include "core/HelperFunctions.hpp"
#include "Config.hpp"
#include "Constants.hpp"

using namespace std;

/**
 * Assertions::assertAreConfigDataFields()
 */
void Assertions::assertAreConfigDataFields(const vector<string> &data_fields){
    if (data_fields.empty()) throw runtime_error("The data fields vector is empty.");

    vector<string> valid_data_fields = Config::getConstraints().getMemberNames();

    for (const string &member : data_fields){
        if (findIndexOfStringInVector(valid_data_fields, member) == -1)
            throw runtime_error("The data field '" + member + "' is not valid.");
    }
}

/**
 * Assertions::assertDataFieldConfig()
 */
void Assertions::assertDataFieldConfig(const Json::Value &data_field_config){
    if (data_field_config.size() != DATA_FIELDS_CONFIG_NUM_JSON_FIELDS)
        throw runtime_error("Data field configuration fields are missing or are in excess.");

    // Asserts the options list
    if (!data_field_config.isMember(OPTION_LISTS) || !data_field_config[OPTION_LISTS].isObject())
        throw runtime_error("The options list member is missing in the configuration file.");

    Json::Value option_lists = data_field_config[OPTION_LISTS];
    vector<string> option_names = option_lists.getMemberNames();
    for(string list : option_names){
        if (!option_lists[list].isArray())
            throw runtime_error("The configuration options list '" + list + "' is not an array.");

        if (option_lists[list].empty())
            throw runtime_error("The configuration options list '" + list + "' is empty.");

        // Assert options content
        for(int index = 0; index < option_lists[list].size(); index++){
            if (!option_lists[list][index].isString())
                throw runtime_error("The options list '" + list + "'s at index '" + to_string(index) + "' is not a string.");

        }
    }

    // Asserts the data fields constraints
    if (!data_field_config.isMember(CONSTRAINTS) || !data_field_config[CONSTRAINTS].isObject())
        throw runtime_error("The constraints member is missing in the configuration file.");
    
    Json::Value constraints = data_field_config[CONSTRAINTS];
    if (constraints.empty())
        throw runtime_error("Data field configuration constraints object is empty.");

    for(const string &member : constraints.getMemberNames()){
        if (!constraints[member].isObject())
            throw runtime_error("The data field configuration member '" + member + "' is not a Json object.");
        
        if (constraints[member].size() != 2)
            throw runtime_error("The data field configuration member '" + member + "' contains keys that should not be there.");        
        if ((constraints[member].isMember(INPUT_TYPE) && constraints[member].isMember(OPTIONS)) == false && 
            (constraints[member].isMember(INPUT_TYPE) && constraints[member].isMember(MAX_CHARS)) == false)
            throw runtime_error("The data field configuration member '" + member + "' does not map to a valid object.");        
        
        // Check validity of the input type
        if (!constraints[member][INPUT_TYPE].isString())
            throw runtime_error("The data field configuration member '" + member + "'s input type is not a string.");

        string input_type = constraints[member][INPUT_TYPE].asString();
        if (input_type == STRING || input_type == INTEGER){
            if (!constraints[member].isMember(MAX_CHARS)){
                throw runtime_error("An data field string or integer input type does not have max-chars configuration.");
            }else if (!constraints[member][MAX_CHARS].isInt()){
                throw runtime_error("Data field configuration '" + member + "' does not have an integer max-chars.");
            }else if(constraints[member][MAX_CHARS].asInt() <= 0){
                throw runtime_error("Data field configuration '" + member + "'s integer max-chars is not a positive number.");
            }
        }else if (input_type == OPTIONS){
            if (!constraints[member].isMember(OPTIONS)){
                throw runtime_error("Options input type for data field configuration member '" + member + "' does not have options member.");
            }else if (!constraints[member][OPTIONS].isString()){
                throw runtime_error("Data field configuration '" + member + "' does not have an string option.");
            }else if (findIndexOfStringInVector(option_names, constraints[member][OPTIONS].asString()) == -1){
                throw runtime_error("Data field configuration '" + member + "' does not specify an existing option list.");
            }
        }else{
            throw runtime_error("Data field configuration '" + member + "'s input type is invalid.");
        }
    }
}

/**
 * Assertions::assertValidRawUpdateJson()
 */
void Assertions::assertValidRawUpdateJson(Json::Value raw_update_json){
    // Checks that the basic members exist
    if (raw_update_json.size() != DATA_FIELDS_UPDATE_NUM_JSON_FIELDS)
        throw runtime_error("Data update json fields are missing or are in excess.");

    if (!raw_update_json.isMember(USER_ID) || !raw_update_json[USER_ID].isString())
        throw runtime_error("Data update is missing the user id.");
    
    if (!raw_update_json.isMember(ENCRYPTED_DATA_FIELDS) || !raw_update_json[ENCRYPTED_DATA_FIELDS].isString())
        throw runtime_error("Data update is missing the encrypted data fields.");
}

/**
 * Assertions::assertValidEncryptedUpdateDataFields()
 */
void Assertions::assertValidEncryptedUpdateDataFields(Json::Value encrypted_update_data_fields){
    // Check that the data fields contains field names
    // that are present in the configuration file.
    vector<string> data_fields = encrypted_update_data_fields[EXPECTED_DATA_FIELDS].getMemberNames();
    Assertions::assertAreConfigDataFields(data_fields);

    // Check that the value of each member is a string
    for (const string& field: data_fields){
        if (!encrypted_update_data_fields[field].isString())
            throw runtime_error("The data field " + field + " does not map to a string.");
    }
}

/**
 * Assertions::assertValidRawRequestJson()
 */
void Assertions::assertValidRawRequestJson(Json::Value raw_request_json){
    // Checks that the basic members exist
    if (raw_request_json.size() != DATA_FIELDS_REQUEST_NUM_JSON_FIELDS)
        throw runtime_error("Data request json fields are missing or are in excess.");

    if (!raw_request_json.isMember(REQUEST_ID) || !raw_request_json[REQUEST_ID].isString())
        throw runtime_error("Data request is missing the request id.");

    if (!raw_request_json.isMember(USER_ID) || !raw_request_json[USER_ID].isString())
        throw runtime_error("Data request is missing the user id.");
    
    if (!raw_request_json.isMember(EXPECTED_DATA_FIELDS) || !raw_request_json[EXPECTED_DATA_FIELDS].isArray())
        throw runtime_error("Data request is missing the expected data fields.");

    if (!raw_request_json.isMember(PUBLIC_KEYS) || !raw_request_json[PUBLIC_KEYS].isString())
        throw runtime_error("Data request is missing the public keys.");

    if (!raw_request_json.isMember(PRIVATE_KEYS) || !raw_request_json[PRIVATE_KEYS].isString())
        throw runtime_error("Data request is missing the private keys.");

    // Check that the expected data fields contains field names
    // that are present in the configuration file.
    vector<string> expected_data_fields = raw_request_json[EXPECTED_DATA_FIELDS].getMemberNames();
    Assertions::assertAreConfigDataFields(expected_data_fields);
}

/**
 * Assertions::assertValidKeysJsonFormat()
 */
void Assertions::assertValidKeysJsonFormat(Json::Value keys_json){
    // Check that the json is an object
    if (!keys_json.isObject())
        throw runtime_error("The keys json is not an object.");

    // Validate that all of the data-field names are within the config file
    vector<string> data_fields = keys_json.getMemberNames();
    Assertions::assertAreConfigDataFields(data_fields);

    // Check that each member maps to an string
    for(const string& field: data_fields){
        if (!keys_json[field].isString())
            throw runtime_error("The keys data field " + field + " does not map to a string.");
    }
}

/**
 * Assertions::assertMatchingStringElements()
 */
void Assertions::assertMatchingStringElements(vector<string> expected, vector<string> actual){
    if (expected.size() != actual.size()){
        throw runtime_error("The string vectors are not of the same length.");
    }    
    
    // Checks that each element from expected exists in actual
    for (const string& element: expected){       
        // Throw if an element of exepcted was not found in actual
        if (findIndexOfStringInVector(actual, element) == -1){
            throw runtime_error("An expected string element did not appear in the actual string vector.");
        }
    }
}
