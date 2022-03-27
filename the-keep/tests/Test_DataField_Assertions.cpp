/**
 * @filename: Test_DataField_Assertions.cpp
 * @description: To test the Assertions class for data fields of the Keep.
 * @author: KeepId
 * @date: March 27, 2022
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include "test_common.hpp"
#include "../core/data-fields/Constants.hpp"
#include "../core/data-fields/Config.hpp"
#include "../core/data-fields/Assertions.hpp"

using namespace std;

const string INVALID_CONFIG = SAMLE_DATA_FIELDS + "invalid_config_jsons/";
const string INVALID_REQUEST = SAMLE_DATA_FIELDS + "invalid_request_jsons/";
const string INVALID_UPDATE = SAMLE_DATA_FIELDS + "invalid_update_jsons/";

/**
 * Test_ValidConfigFile - Test that a valid data field config files does not cause
 *                        any error to occur when being asserted for correctness.
 */
TEST(TestDataField_Assertions, Test_ValidConfigFile){
    // Sets up the test
    copyFile(SAMLE_DATA_FIELDS + "config_valid.json", DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Create test objects
    vector<string> data_fields {"name_FirstName", "name_LastName", "address_City"};
    Json::Value data_field_config = extractJsonValue(SAMLE_DATA_FIELDS + "config_valid.json");
    Json::Value data_update_input = extractJsonValue(SAMLE_DATA_FIELDS + "update_valid.json");
    Json::Value data_request_input = extractJsonValue(SAMLE_DATA_FIELDS + "request_valid.json");

    // Tests the json objects for correctness
    EXPECT_NO_THROW(Assertions::assertValidDataFields(data_fields));
    EXPECT_NO_THROW(Assertions::assertDataFieldConfig(data_field_config));
    EXPECT_NO_THROW(Assertions::assertValidDataUpdate(data_update_input));
    EXPECT_NO_THROW(Assertions::assertValidDataRequest(data_request_input));

    // Takes down the test
    Config::uninitialize();
}

/**
 * TestMethodThrows_assertValidDataFields - Test that the method assertValidDataFields() correctly 
 *              throws when invalid data_fields (compared to Config) are passed within the list.
 */
TEST(TestDataField_Assertions, TestMethodThrows_assertValidDataFields){
    // Sets up the test
    copyFile(SAMLE_DATA_FIELDS + "config_valid.json", DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Creates sample data field lists
    vector<string> dt_empty{};
    vector<string> dt_empty_str{""};
    vector<string> dt_one{"invalid_address_Country"};
    vector<string> dt_invalid_some{"billing_FirstName", "name_FirstName", "invalid_data_field"};
    vector<string> dt_invalid_all{"invalid_data_field", "probably_not_valid", "maybe_valid"};

    // Tests that assertValidDataFields() throws as expected
    EXPECT_THROW(Assertions::assertValidDataFields(dt_empty), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataFields(dt_empty_str), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataFields(dt_one), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataFields(dt_invalid_some), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataFields(dt_invalid_all), runtime_error);

    // Takes down the test
    Config::uninitialize();
}

/**
 * TestMethodThrows_assertDataFieldConfig - Test that the method assertDataFieldConfig() 
 *                          correctly throws when invalid json values are passed into it.
 */
TEST(TestDataField_Assertions, TestMethodThrows_assertDataFieldConfig){
    // Test the reference file
    EXPECT_NO_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_valid_reference.json")));

    // Test invalid general config setups   
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_file_empty.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_unknown_key.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_option_lists_missing.json")), runtime_error);

    // Test invalid general constraints setups
    // EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_constraint_duplicate.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_empty.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_not_dictionary.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_unknown_key.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_data_field_not_dictionary.json")), runtime_error);
    
    // Test invalid constraint input_type setups
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_input_type_invalid_key_word.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_input_type_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_input_type_not_string_type.json")), runtime_error);
    
    // Test invalid constraint max_chars setups
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_max_chars_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_max_chars_negative.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_max_chars_not_int_type.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_max_chars_not_needed.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_max_chars_zero.json")), runtime_error);
    
    // Test invalid constraint options setups
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_options_invalid_reference.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_options_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_options_not_needed.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_constraints_options_not_string_type.json")), runtime_error);
    
    // Test invalid constraint option_lists setups
    // EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_option_lists_options_content_duplicate.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_option_lists_options_contents_not_string_type.json")), runtime_error);
    // EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_option_lists_options_duplicate.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_option_lists_options_empty.json")), runtime_error);
    EXPECT_THROW(Assertions::assertDataFieldConfig(extractJsonValue(INVALID_CONFIG + "config_invalid_option_lists_options_is_not_list.json")), runtime_error);
}

/**
 * TestMethodThrows_assertValidDataUpdate - Test that the method assertValidDataUpdate() 
 *                          correctly throws when invalid json values are passed into it.
 */
TEST(TestDataField_Assertions, TestMethodThrows_assertValidDataUpdate){
    // Sets up the test
    copyFile(SAMLE_DATA_FIELDS + "config_valid.json", DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    EXPECT_NO_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_valid_reference.json")));

    // Test invalid general update setups
    // EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_duplicate_key.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_file_empty.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_unknown_key.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_user_id_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_encrypted_data_fields_missing.json")), runtime_error);

    // Test invalid user_id setups
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_user_id_not_string_type.json")), runtime_error);

    // Test invalid encrypted_data_fields setups
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_encrypted_data_fields_empty.json")), runtime_error);
    // EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_encrypted_data_fields_entry_duplicate.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_encrypted_data_fields_entry_invalid.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_encrypted_data_fields_entry_not_string_type.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataUpdate(extractJsonValue(INVALID_UPDATE + "update_invalid_encrypted_data_fields_not_dictionary_type.json")), runtime_error);

    // Takes down the test
    Config::uninitialize();
}

/**
 * TestMethodThrows_assertValidDataRequest - Test that the method assertValidDataRequest() 
 *                          correctly throws when invalid json values are passed into it.
 */
TEST(TestDataField_Assertions, TestMethodThrows_assertValidDataRequest){
    // Sets up the test
    copyFile(SAMLE_DATA_FIELDS + "config_valid.json", DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    EXPECT_NO_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_valid_reference.json")));

    // Test invalid general request setups
    // EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_duplicate_key.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_file_empty.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_unknown_key.json")), runtime_error);

    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_private_keys_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_public_keys_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_request_id_missing.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_user_id_missing.json")), runtime_error);

    // Test invalid private_keys setups
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_private_keys_empty.json")), runtime_error);
    // EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_private_keys_entry_duplicate.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_private_keys_entry_invalid.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_private_keys_entry_not_string_type.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_private_keys_not_dictionary_type.json")), runtime_error);

    // Test invalud public_keys setups
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_public_keys_empty.json")), runtime_error);
    // EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_public_keys_entry_duplicate.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_public_keys_entry_invalid.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_public_keys_entry_not_string_type.json")), runtime_error);
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_public_keys_not_dictionary_type.json")), runtime_error);

    // Test invalid request_id setups
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_request_id_not_string_type.json")), runtime_error);

    // Test invalid user_id setups
    EXPECT_THROW(Assertions::assertValidDataRequest(extractJsonValue(INVALID_REQUEST + "request_invalid_user_id_not_string_type.json")), runtime_error);

    // Take down the test
    Config::uninitialize();
}
