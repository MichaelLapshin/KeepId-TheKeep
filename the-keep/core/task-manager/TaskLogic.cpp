/**
 * @filename: TaskLogic.cpp
 * @description: Implementation of the logic that is executed within a task.
 * @author: KeepId 
 * @date: March 6, 2022
 */
#include <jsoncpp/json/json.h>

#include "core/HelperFunctions.hpp"
#include "core/key-manager/KeyManager.hpp"
#include "core/data-fields/Assertions.hpp"
#include "core/data-fields/Constants.hpp"
#include "core/data-fields/Config.hpp"
#include "TaskLogic.hpp"

using namespace std;

/**
 * workLoop()
 * @brief The method that would be run whenever
 *        the task manager is started.
 */
void workLoop(const atomic<bool> &loop_thread){
    while(loop_thread){
        /////////////////////////////////////////////
        ///  Poll and execute user-data updating  ///
        /////////////////////////////////////////////
        try {
            const string data_update_str_json; // = MessageClient.PollFetchDataUpdate() // Contains user_id, encrypted_data_fields
            userDataUpdateTask(data_update_str_json);
        } catch(const std::runtime_error& exception) {
            // TODO: Log the exception
            // TODO: Redact and propagate the issue back to the user. -> TODO: Need custom error-class object for returning errors to the user.
        }

        /////////////////////////////////////////////
        ///     Poll and execute data-request     ///
        /////////////////////////////////////////////
        try {
            const string data_request_str_json; // = MessageClient.fetchUserDataRequest() // Contains user_id, request_id, private_keys, public_keys
            userDataRequestTask(data_request_str_json);
        } catch(const std::runtime_error& exception) {
            // TODO: Log the exception.
            // TODO: Redact and ropagate the issue back to the user. -> TODO: Need custom error-class object for returning errors to the user.
        }
    }
}

/**
 * dataUpdateTask()
 * @brief Performs the user data database update task.
 * 
 * @param[in] data_update_input The data to update the database with.
 */
void userDataUpdateTask(const string& raw_data_update_str){
    // Obtains the raw data
    const Json::Value& raw_data_update_json = parseJsonString(raw_data_update_str);
    Assertions::assertValidRawUpdateJson(raw_data_update_json);
    const string& user_id = raw_data_update_json[USER_ID].asString();
    const string& keep_encrypted_data_fields = raw_data_update_json[ENCRYPTED_DATA_FIELDS].asString();

    // Decrypts and validates the encrypted data fields
    
    const string& keep_decrypted_data_fields = KeyManager::decryptMessage(keep_encrypted_data_fields);
    const Json::Value& encrypted_data_fields_json = parseJsonString(keep_decrypted_data_fields);
    Assertions::assertValidEncryptedUpdateDataFields(encrypted_data_fields_json);

    // Updates the Keep's database
    // HolyCow.storeUserData(user_id, encrypted_data_fields_json); 
}

/**
 * userDataRequestTask()
 * @brief Performs the user data request task.
 * 
 * @param[in] data_request_input The data request input Json.
 */
// void userDataRequestTask(Json::Value data_request_input){
void userDataRequestTask(const string& raw_data_request_str){
    ////////////////////////////////////////////////////
    // Parse and Validate the Input
    ////////////////////////////////////////////////////
    // Parses and validates the raw data request form
    const Json::Value& raw_data_request_json = parseJsonString(raw_data_request_str);
    Assertions::assertValidRawRequestJson(raw_data_request_json);

    // Parses the unencrypted entries
    const string& user_id = raw_data_request_json[USER_ID].asString();
    const string& request_id = raw_data_request_json[REQUEST_ID].asString();

    const int num_expected_data_fields = raw_data_request_json[EXPECTED_DATA_FIELDS].size();
    vector<string> expected_data_fields = raw_data_request_json[EXPECTED_DATA_FIELDS].getMemberNames();

    // Decrypts and records the public keys
    const string& keep_encrypted_public_keys = raw_data_request_json[PUBLIC_KEYS].asString();
    const string& keep_decrypted_public_keys = KeyManager::decryptMessage(keep_encrypted_public_keys);
    const Json::Value public_keys = parseJsonString(keep_decrypted_public_keys);

    // Decrypts and records the private keys
    const string& keep_encrypted_private_keys = raw_data_request_json[PUBLIC_KEYS].asString();
    const string& keep_decrypted_private_keys = KeyManager::decryptMessage(keep_encrypted_private_keys);
    const Json::Value& private_keys = parseJsonString(keep_decrypted_private_keys);

    // Assert that the given information is valid
    Assertions::assertAreConfigDataFields(expected_data_fields);
    Assertions::assertValidKeysJsonFormat(public_keys);
    Assertions::assertValidKeysJsonFormat(private_keys);
    Assertions::assertMatchingStringElements(expected_data_fields, public_keys.getMemberNames()); 
    Assertions::assertMatchingStringElements(expected_data_fields, private_keys.getMemberNames());

    // Validate the public and private keys
    for (const string& field: expected_data_fields){
        if (!KeyManager::validatePublicKey(public_keys[field].asString())){
            throw runtime_error("A public key could not be validated.");
        }else if (!KeyManager::validatePrivateKey(private_keys[field].asString())){
            throw runtime_error("A private key could not be validated.");
        }
    }

    ////////////////////////////////////////////////////
    // Re-encrypte the Keep's Data
    ////////////////////////////////////////////////////
    const Json::Value encrypted_data; // = HolyCow.fetchKeepUserData(user_id, data_fields);
    Json::Value decrypted_data;
    Json::Value reencrypted_data;

    for (const string &field : expected_data_fields){
        // Decrypts the data
        decrypted_data[field] = KeyManager::decryptMessage(encrypted_data[field].asString(),
                                                           private_keys[field].asString());
        // Re-encrypts the data
        reencrypted_data[field] = KeyManager::encryptMessage(decrypted_data[field].asString(),
                                                             public_keys[field].asString());
    }

    // Updates the Keep's database
    // HolyCow.storeUserData(user_id, reencrypted_data); 

    ////////////////////////////////////////////////////
    // Validate the Decrypted Data Fields
    ////////////////////////////////////////////////////
    const vector<string> &invalid_fields = Config::validateDecryptedDataFields(decrypted_data);
    if (!invalid_fields.empty()){
        throw runtime_error("There are invalid data fields.");
        // Send an error message to the user
        // OutputMessageClient.forwardInvalidUserDataFields(request_id, invalid_fields);
    }

    ////////////////////////////////////////////////////
    // Prepare and Forward User Data to Client Company
    ////////////////////////////////////////////////////
    // Generating temporary keys (for the client company)
    const pair<string, string> key_pair = KeyManager::generateKeyPair();
    const string& temp_public_key = key_pair.first;
    const string& temp_private_key = key_pair.second;

    // Prepares the user data to send to the client company
    Json::Value data_to_forward;
    for (const string& field: expected_data_fields){
        data_to_forward[field] = decrypted_data[field].asString();
    }

    const string& encrypted_data_to_forward = KeyManager::encryptMessage(data_to_forward.asString(),
                                                                         temp_public_key);

    // Forwards the company encrypted data
    // OutputMessageClient.forwardCompanyEncryptedData(request_id, encrypted_data_to_forward);

    // Forwards the private key
    // OutputMessageClient.forwardCompanyPrivateKey(request_id, temp_private_key);
}