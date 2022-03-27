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
         * Assertions::assertValidDataFields()
         * @brief Asserts that all the given data fields are valid according
         *        to the data field configuration file.
         * 
         * @param[in] data_fields A list of data fields to validate.
         */
        static void assertValidDataFields(const vector<string>& data_fields);

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
         * Assertions::assertValidDataUpdate()
         * @brief Asserts that the given data request JSON satisfies the update constraints.
         * 
         * @param[in] data_update_input The Json object containing the user_id and the encrypted
         *                          data fields to update the Holy Cow with.
         * @throw
         */
        static void assertValidDataUpdate(const Json::Value& data_update_input);
        
        /**
         * Assertions::assertValidDataRequest()
         * @brief Asserts that the given data request JSON satisfies its constraints.
         * 
         * @param[in] data_request_input Json object of the data request input.
         * 
         * @throw No user id member that maps to a string
         * @throw No request id memeber that maps to a string
         * @throw No data field member that maps to an object
         * @throw Data field is empty
         * @throw Data field members are not within the configurations file
         * @throw Data field members are not strings
         * @throw A public-private key pair is not given
         */
        static void assertValidDataRequest(const Json::Value& data_request_input);  
};
