#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

#include "test_common.hpp"
#include "../core/data-fields/Constants.hpp"
#include "../core/data-fields/Config.hpp"
#include "../core/data-fields/Assertions.hpp"

using namespace std;

const string SMPL_DF_CNFG = "./sample_data_fields/";

/**
 * extractJsonValue()
 * @brief Reads and records the json structure found within the file
 *        into a Json::Value object.
 * 
 * @param[in] file_path The file to read from.
 * 
 * @return The json value representing the json structure within the file.
 */
Json::Value extractJsonValue(string file_path){
    Json::Value extracted_json;
    const char* json_contents_c_string = readFile(file_path).c_str();
    Json::CharReaderBuilder json_builder;
    string err_msg;
    bool parse_success = json_builder.newCharReader()->parse(
                            json_contents_c_string /* begin */, 
                            json_contents_c_string + strlen(json_contents_c_string) /* end */, 
                            &extracted_json /* root */,
                            &err_msg /* errs */);
    return extracted_json;
} 

/**
 * Test_ValidConfigFile - Test that a valid data field config files does not cause
 *                        any error to occur when being asserted for correctness.
 */
TEST(TestDataField_Assertions, Test_ValidConfigFile){
    // Sets up the test
    copyFile(SMPL_DF_CNFG + "config_valid.json", DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Create test objects
    vector<string> data_fields {"name_FirstName", "name_LastName",
                                "address_StreetAddress", "address_City", "address_PostalCode"};
    Json::Value data_field_config = extractJsonValue(SMPL_DF_CNFG + "config_valid.json");
    Json::Value data_update_input = extractJsonValue(SMPL_DF_CNFG + "update_valid.json");
    Json::Value data_request_input = extractJsonValue(SMPL_DF_CNFG + "request_valid.json");

    // Tests the json objects for correctness
    EXPECT_NO_THROW(Assertions::assertValidDataFields(data_fields));
    EXPECT_NO_THROW(Assertions::assertDataFieldConfig(data_field_config));
    EXPECT_NO_THROW(Assertions::assertValidDataUpdate(data_update_input));
    EXPECT_NO_THROW(Assertions::assertValidDataRequest(data_request_input));

    // Takes down the test
    Config::uninitialize();
}

/**
 * TestMethod_assertValidDataFields - Test that the method assertValidDataFields() correctly 
 *      throws when invalid data_fields (compared to Config) are passed within the list.
 * 
 */
TEST(TestDataField_Assertions, TestMethod_assertValidDataFields){
    // Sets up the test
    copyFile(SMPL_DF_CNFG + "config_valid.json", DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Creates sample data field lists
    vector<string> dt_empty{};
    vector<string> dt_empty_str{""};
    vector<string> dt_one{"abc"};
    vector<string> dt_valid{};
    vector<string> dt_invalid{};

    // Takes down the test
    Config::uninitialize();
}