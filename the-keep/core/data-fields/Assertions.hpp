/**
 * @filename: Assertions.hpp
 * @description: Declares the common assertions associated with data-fields.
 * @author: KeepId
 * @date: February 19, 2022
 */

#include <jsoncpp/json/json.h>

class Assertions{
    public:
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
        static void assertDataFieldConfig(Json::Value& data_field_config);

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
         */
        static void assertValidDataRequest(Json::Value& data_request_input);
};
