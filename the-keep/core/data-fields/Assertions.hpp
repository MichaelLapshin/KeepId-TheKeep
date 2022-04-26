/**
 * @filename: Assertions.hpp
 * @description: Declares the common assertions associated with data-fields.
 * @author: KeepId
 * @date: February 19, 2022
 */

#pragma once

#include <jsoncpp/json/json.h>

using namespace std;

class Assertions{
public:
    /**
     * Assertions::assertAreConfigDataFields()
     * @brief Asserts that all the given data fields are valid according
     *        to the data field configuration file.
     * 
     * @param[in] data_fields A list of data fields to validate.
     * 
     * @throw The passed data fields is empty
     * @throw A data field is not within the configuration list
     */
    static void assertAreConfigDataFields(const vector<string>& data_fields);

    /**
     * Assertions::assertDataFieldConfig()
     * @brief Asserts that the Json parsed configurations satisfies its constraints.
     * 
     * @param[in] data_field_config The Json object of the data fields configuration.
     * 
     * @throw Options list is missing
     * @throw Options contains non-array members
     * @throw Constraints is missing
     * @throw Constraints contains non-object members
     * @throw Constraints data field format is invalid
     */
    static void assertDataFieldConfig(const Json::Value& data_field_config);

    /**
     * Assertions::assertValidRawUpdateJson()
     * @brief Assert that the provided json object sent from the User Encrypted
     *        Data server to update the user data is of the correct format.
     * 
     * @param[in] raw_update_json The json object obtained from parsing the 
     *                            date update json string.
     * 
     * @throw Too many or too little number of json fields.
     * @throw User ID member does not exist.
     * @throw Encrypted data fields member does not exist.
     */
    static void assertValidRawUpdateJson(Json::Value raw_update_json);

    /**
     * Assertions::assertValidEncryptedUpdateDataFields()
     * @brief Assert that the format of the encrypted data
     *        fields used to update user data is correct.
     * 
     * @param[in] encrypted_update_data_fields The encrypted data fields json to validate.
     * 
     * @throw The member names are not within the configuration file.
     * @throw The value of field is not a string.
     */
    static void assertValidEncryptedUpdateDataFields(Json::Value encrypted_update_data_fields);

    /**
     * Assertions::assertValidRawRequestJson()
     * @brief Assert that the provided json object sent from the User Response
     *        server to forward data is of the correct format.
     * 
     * @param[in] raw_request_json The json object obtained from parsing the 
     *                            date request json string. 
     * 
     * @throw Too many or too little number of json fields.
     * @throw Request ID member does not exist.
     * @throw User ID member does not exist.
     * @throw Expected data fields member does not exist.
     * @throw Public keys member does not exist.
     * @throw Private keys member does not exist.
     */
    static void assertValidRawRequestJson(Json::Value raw_request_json);

    /**
     * Assertions::assertValidKeysJsonFormat()
     * @brief Assert that the json format used to store the keys is correct.
     * 
     * @param[in] keys_json The json object of the decrypted keys passed in
     *                      order to forward requested user data.
     * 
     * @throw The passed json is not an object.
     * @throw The data fields within the object are not in the config file.
     * @throw The members of the json object do not map to strings.
     */
    static void assertValidKeysJsonFormat(Json::Value keys_json);

    /**
     * Assertions::assertMatchingStringElements()
     * @brief Assert that two string vectors are identical, not considering the order.
     * 
     * @param[in] expected The expected vector of strings we are testing against.
     * @param[in] actual   The actual vector of string we are testing.
     * 
     * @throw The two string vectors are not equal in length.
     * @throw An element of the expected vector was not found in the actual vector.
     */
    static void assertMatchingStringElements(vector<string> expected, vector<string> actual);
};
