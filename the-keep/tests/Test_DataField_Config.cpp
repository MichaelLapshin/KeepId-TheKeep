/**
 * @filename: Test_DataField_Config.cpp
 * @description: To test the Config class for data fields of the Keep.
 * @author: KeepId
 * @date: March 27, 2022
 */

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "test_common.hpp"
#include "../core/data-fields/Constants.hpp"
#include "../core/data-fields/Config.hpp"

using namespace std;

const string VALID_CONFIG = SAMLE_DATA_FIELDS + "config_valid.json";
const string RANDOM_FILE = SAMLE_DATA_FIELDS + "random.json";
const string INVALID_CONFIG = SAMLE_DATA_FIELDS + "invalid_config_jsons/";
const string DECRYPTED_DATA = SAMLE_DATA_FIELDS + "decrypted_data_jsons/";

/**
 * testConfigInitFail()
 * @brief A helper method used to initialize 
 * 
 * @param[in] file_path The path to the config file to test.
 */
void testConfigInitFail(string file_path){
    copyFile(file_path, DATA_FIELD_CONFIG_FILE_NAME);
    EXPECT_THROW(Config::initialize(), runtime_error);
    EXPECT_THROW(Config::uninitialize(), runtime_error);
}

/**
 * Initialize - Test that a correct initialization of Config does not throw
 *              an error. Follow up initializations would throw and error.
 */
TEST(TestDataField_Config, Initialize){
    // Sets up the test
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);

    // Tests the initialize() method
    EXPECT_NO_THROW(Config::initialize());
    EXPECT_THROW(Config::initialize(), runtime_error);

    // Take down the test
    Config::uninitialize();
}

/**
 * Initialize_ParsingError - Test that the initialization of Config with an
 *          incorrect random text file throws an error.
 */
TEST(TestDataField_Config, Initialize_ParsingError){
    // Test that random content would result in a throw.
    copyFile(RANDOM_FILE, DATA_FIELD_CONFIG_FILE_NAME);
    EXPECT_THROW(Config::initialize(), runtime_error);
}

/**
 * Initialize_ParsingError - Test that the initialization of Config with an
 *          incorrect random text file throws an error.
 */
TEST(TestDataField_Config, Initialize_ConfigAssertions){
    // Test the reference file
    copyFile(INVALID_CONFIG + "config_invalid_valid_reference.json", DATA_FIELD_CONFIG_FILE_NAME);
    EXPECT_NO_THROW(Config::initialize());
    EXPECT_NO_THROW(Config::uninitialize());

    // Test invalid general config setups   
    testConfigInitFail(INVALID_CONFIG + "config_invalid_file_empty.json") ;
    testConfigInitFail(INVALID_CONFIG + "config_invalid_unknown_key.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_missing.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_option_lists_missing.json");

    // Test invalid general constraints setups
    // testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_constraint_duplicate.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_empty.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_not_dictionary.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_unknown_key.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_data_field_not_dictionary.json");
    
    // Test invalid constraint input_type setups
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_input_type_invalid_key_word.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_input_type_missing.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_input_type_not_string_type.json");
    
    // Test invalid constraint max_chars setups
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_max_chars_missing.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_max_chars_negative.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_max_chars_not_int_type.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_max_chars_not_needed.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_max_chars_zero.json");
    
    // Test invalid constraint options setups
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_options_invalid_reference.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_options_missing.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_options_not_needed.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_constraints_options_not_string_type.json");
    
    // Test invalid constraint option_lists setups
    // testConfigInitFail(INVALID_CONFIG + "config_invalid_option_lists_options_content_duplicate.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_option_lists_options_contents_not_string_type.json");
    // testConfigInitFail(INVALID_CONFIG + "config_invalid_option_lists_options_duplicate.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_option_lists_options_empty.json");
    testConfigInitFail(INVALID_CONFIG + "config_invalid_option_lists_options_is_not_list.json");
}

/**
 * Uninitialize - Test that the uninitialization of Config is done correctly.
 */
TEST(TestDataField_Config, Uninitialize){
    // Test that an error is thrown when Config is not initialized
    EXPECT_THROW(Config::uninitialize(), runtime_error);

    // Test that the Config is correct unintialized when it is initialized.
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);
    EXPECT_NO_THROW(Config::initialize());
    EXPECT_NO_THROW(Config::uninitialize());

    // Test that two consecutive unintializations throw an error.
    EXPECT_THROW(Config::uninitialize(), runtime_error);
}

/**
 * GetOptionLists_Uninitialized - Test that the Config method getOptionLists()
 *          correctly throws an error when no configuration was initialized.
 */
TEST(TestDataField_Config, GetOptionLists_Uninitialized){
    EXPECT_THROW(Config::getOptionLists(), runtime_error);
}

/**
 * GetOptionLists - Test that the method getOptionLists() of an initialized
 *            Config correctly returns the option lists.
 */
TEST(TestDataField_Config, GetOptionLists_Initialized){ 
    // Sets up the test
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Tests that the config output matches what was in the file
    Json::Value expected = extractJsonValue(VALID_CONFIG);
    EXPECT_EQ(expected[OPTION_LISTS], Config::getOptionLists());

    // Take down the test
    Config::uninitialize();
}


/**
 * GetConstraints_Uninitialized - Test that the Config method getConstraints()
 *          correctly throws an error when no configuration was initialized.
 */
TEST(TestDataField_Config, GetConstraints_Uninitialized){
    EXPECT_THROW(Config::getConstraints(), runtime_error);
}

/**
 * GetConstraints_Initialized - Test that the method getConstraints()
 *      of an initialized Config correctly returns the constraints.
 */
TEST(TestDataField_Config, GetConstraints_Initialized){
    // Sets up the test
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Tests that the config output matches what was in the file
    Json::Value expected = extractJsonValue(VALID_CONFIG);
    EXPECT_EQ(expected[CONSTRAINTS], Config::getConstraints());

    // Take down the test
    Config::uninitialize();
}

/**
 * ValidateDecryptedDataFields_Valid - Test that the method validateDecryptedDataFields()
 *              correctly throws when some data fields are invalid.
 */
TEST(TestDataField_Config, ValidateDecryptedDataFields_Invalid){
    // Sets up the test
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();
    
    // Tests
    EXPECT_TRUE(Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_no_invalid.json")).empty());

    // Take down the test
    Config::uninitialize();
}

/**
 * ValidateDecryptedDataFields_Invalid - Test that for valid decrypted data fields the
 *          method validateDecryptedDataFields() correctly validates its input.
 */
TEST(TestDataField_Config, ValidateDecryptedDataFields_Valid){
    // Sets up the test
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();

    // Expected results
    vector<string> 
    expected_invalid_single_opt_invalid = {
        "payment_CardType" // MyCard
    },
    expected_invalid_single_str_max_chars = {
        "address_PostalCode" // L8R1F3K2
    },
    expected_invalid_single_int_max_chars = {
        "billing_PhoneNumber" // 1234567890987654321
    },
    expected_invalid_single_int_str_chars = {
        "payment_ExpirationMonth" // April
    }, 
    expected_invalid_multi_opt_invalid = {
        "payment_CardType", // SomeCard
        "address_Province", // Washington 
        "billing_Province"  // alberta
    },
    expected_invalid_multi_all = {
        "name_MiddleName",        // some very long middle name that is especially longer than 40 characters.
        "address_City",           // another very long string that is supposed to be a city.
        "payment_ExpirationYear", // 20025
        "billing_Province"        // ontario
    },
    expected_invalid_multi_all_2 = {
        "payment_CardType",      // SomeCardType
        "billing_StreetAddress", // one very long street address that is definitely longer than 28 characters.
        "payment_SecurityCode",  // 12345
        "payment_CardNumber",    // 1234y
        "address_Province"       // QuebEc
    };

    // Obtains the invalid data field vectors from sample Json files.
    vector<string>
    actual_invalid_single_opt_invalid = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_single_opt_invalid.json")),
    actual_invalid_single_str_max_chars = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_single_str_max_chars.json")),
    actual_invalid_single_int_max_chars = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_single_int_max_chars.json")),
    actual_invalid_single_int_str_chars = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_single_int_str_chars.json")),
    actual_invalid_multi_opt_invalid = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_multi_opt_invalid.json")),
    actual_invalid_multi_all = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_multi_all.json")),
    actual_invalid_multi_all_2 = Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_multi_all_2.json"));

    // Compares the actual to the expected values
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_single_opt_invalid, actual_invalid_single_opt_invalid));
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_single_str_max_chars, actual_invalid_single_str_max_chars));
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_single_int_max_chars, actual_invalid_single_int_max_chars));
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_single_int_str_chars, actual_invalid_single_int_str_chars));
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_multi_opt_invalid, actual_invalid_multi_opt_invalid));
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_multi_all, actual_invalid_multi_all));
    EXPECT_TRUE(vectorsEquivalentContent(expected_invalid_multi_all_2, actual_invalid_multi_all_2));

    // Take down the test
    Config::uninitialize();
}

/**
 * ValidateDecryptedDataFields_Error - Test that the method validateDecryptedDataFields()
 *     correctly throws when some data fields are invalid and when config is not initialized.
 */
TEST(TestDataField_Config, ValidateDecryptedDataFields_Error){
    // Test that the method throws with config not initialized
    EXPECT_THROW(Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_no_invalid.json")), runtime_error);
    
    // Test that the method throws with config initialized
    copyFile(VALID_CONFIG, DATA_FIELD_CONFIG_FILE_NAME);
    Config::initialize();
    EXPECT_THROW(Config::validateDecryptedDataFields(extractJsonValue(DECRYPTED_DATA + "decrypted_data_fields_invalid_names.json")), runtime_error);
    Config::uninitialize();
}
