/**
 * @filename: DataFieldConstants.hpp
 * @description: Defines the constants associated with 
 *               the data configuration file.
 * @author: KeepId
 * @date: February 19, 2022
 */

#include <string>

#if !defined(KEEP_CONSTANTS)
#define KEEP_CONSTANTS 1

// Configurations constants
const std::string DATA_FIELD_CONFIG_FILE_NAME = "data-fields-config.json";
const std::string OPTIONS_LIST = "options_list";
const std::string CONSTRAINTS = "constraints";

// Data transmission constants
const std::string ENCRYPTED_DATA_FIELDS = "encrypted_data_fields";

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

#endif

