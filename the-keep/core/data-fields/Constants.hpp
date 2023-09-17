/**
 * @filename: DataFieldConstants.hpp
 * @description: Defines the constants associated with 
 *               the data configuration file.
 * @author: KeepId
 * @date: February 19, 2022
 */

#pragma once

#include <string>

// A Flat to indicate a Development run (for logging etc)
const bool DEVELOPMENT = true;

// Configuration file
const std::string MAIN_CONFIG_FILE_NAME = "thekeep-config.json";
const std::string LOG_FILE_NAME = "logs/thekeeplog.log";

// Configurations constants
const std::string DATA_FIELD_CONFIG_FILE_NAME = "data-fields-config.json";
const std::string OPTION_LISTS = "option_lists";
const std::string CONSTRAINTS = "constraints";

// Data transmission constants
const std::string ENCRYPTED_DATA_FIELDS = "encrypted_data_fields";
const std::string EXPECTED_DATA_FIELDS = "expected_data_fields";

// Data field constants
const std::string USER_ID = "user_id";
const std::string REQUEST_ID = "request_id";
const std::string PRIVATE_KEYS = "private_keys";
const std::string PUBLIC_KEYS = "public_keys";

const std::string INPUT_TYPE = "input_type"; 
const std::string MAX_CHARS = "max_chars";
const std::string OPTIONS = "options";
const std::string STRING = "string";
const std::string INTEGER = "int";

// Formatting constants
const int DATA_FIELDS_CONFIG_NUM_JSON_FIELDS = 2; // "option_lists", "constraints"
const int DATA_FIELDS_UPDATE_NUM_JSON_FIELDS = 2; // "user_id", "encrypted_data_fields"
const int DATA_FIELDS_REQUEST_NUM_JSON_FIELDS = 5; // "request_id", "user_id", "expected_data_fields", "public_keys", "private_keys"

