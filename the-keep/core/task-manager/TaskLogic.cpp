/**
 * @filename: TaskLogic.cpp
 * @description: Implementation of the logic that is executed within a task.
 * @author: KeepId 
 * @date: March 6, 2022
 */

#include <thread>
#include <atomic>
#include <assert.h>

#include <jsoncpp/json/json.h>

#include "../key-manager/KeyManager.hpp"
#include "../data-fields/Assertions.hpp"
#include "../data-fields/Constants.hpp"
#include "../data-fields/Config.hpp"

using namespace std;

// Function declaration
void workLoop(atomic<bool> &loop_thread);
void userDataUpdateTask(Json::Value data_update_input);
void userDataRequestTask(Json::Value data_request_input);

/**
 * workLoop()
 * @brief The method that would be run whenever
 *        the task manager is started.
 */
void workLoop(atomic<bool> &loop_thread){
    while(loop_thread){
        /////////////////////////////////////////////
        ///  Poll and execute user-data updating  ///
        /////////////////////////////////////////////
        Json::Value data_update_json; // = MessageClient.PollFetchDataUpdate() // Contains user_id, encrypted_data_fields
        userDataUpdateTask(data_update_json);

        /////////////////////////////////////////////
        ///     Poll and execute data-request     ///
        /////////////////////////////////////////////
        const Json::Value data_request_input; // = MessageClient.fetchUserDataRequest() // Contains user_id, request_id, private_keys, public_keys
        userDataRequestTask(data_request_input);
    }
}

/**
 * dataUpdateTask()
 * @brief Performs the user data database update task.
 * 
 * @param[in] data_update_input The data to update the database with.
 */
void userDataUpdateTask(Json::Value data_update_input){
    Assertions::assertValidDataUpdate(data_update_input);

    // Constants
    const string &user_id = data_update_input[USER_ID].asString();
    const Json::Value &encrypted_data_fields = data_update_input[ENCRYPTED_DATA_FIELDS];

    // HolyCow.storeUserData(user_id, encrypted_data); 
}

/**
 * userDataRequestTask()
 * @brief Performs the user data request task.
 * 
 * @param[in] data_request_input The data request input Json.
 */
void userDataRequestTask(Json::Value data_request_input){
    Assertions::assertValidDataRequest(data_request_input);  

    // Constants
    const vector<string> &data_fields = data_request_input[PUBLIC_KEYS].getMemberNames();
    const string &user_id = data_request_input[USER_ID].asString();
    const string &request_id = data_request_input[REQUEST_ID].asString();
    
    // Decrypts the given public and private keys using the Keep's private key
    vector<string> invalid_keys;
    Json::Value public_keys, private_keys;
    for(const string field : data_fields){
        string public_key = KeyManager::decryptMessage(data_request_input[PUBLIC_KEYS].asString());
        string private_key = KeyManager::decryptMessage(data_request_input[PRIVATE_KEYS].asString());

        // Ensures that the given keys are valid
        if (!KeyManager::validatePublicKey(public_key) || !KeyManager::validatePrivateKey(private_key)){
            invalid_keys.push_back(field);
        }else{
            public_keys[field] = public_key;
            private_keys[field] = private_key;  
        }
    }

    if (!invalid_keys.empty()){
        // Forwards the error message if keys are invalid
        // OutputMessageClient.forwardInvalidDataKeys(request_id, invalid_fields);
    }

    // Fetch encrypted user data
    const Json::Value encrytped_data; // = HolyCow.fecthKeepUserData(user_id, data_fields);

    // Decrypt user data
    Json::Value decrypted_data{};
    for(const string &field : data_fields){
        decrypted_data[field] = KeyManager::decryptMessage(encrytped_data[field].asString(),
                                                           private_keys[field].asString());
    }
    Assertions::assertValidDataFields(decrypted_data.getMemberNames());

    // Reencrypts the data
    Json::Value reencrypted_data{};
    for(const string &field : data_fields){
        reencrypted_data[field] = KeyManager::encryptMessage(decrypted_data[field].asString(),
                                                             public_keys[field].asString());
    }
    Assertions::assertValidDataFields(reencrypted_data.getMemberNames());

    // Stores the reencrypted data
    Json::Value data_update_input;
    data_update_input[USER_ID] = user_id;
    data_update_input[ENCRYPTED_DATA_FIELDS] = reencrypted_data;
    userDataUpdateTask(data_update_input); // Sends user_id, encrypted_data_fields

    // Validates the decrypted data
    const vector<string> &invalid_fields = Config::validateDecryptedDataFields(decrypted_data);

    if (invalid_fields.empty()){
        // Generates key pair
        pair<string, string> transmission_key_pair = KeyManager::generateKeyPair();
        string company_public_key = transmission_key_pair.first;
        string company_private_key = transmission_key_pair.second;
        
        // Encrypts the data with the company's key
        Json::Value company_encrypted_data{};
        for(const string &field : data_fields){
            string company_encrypted_message = KeyManager::encryptMessage(decrypted_data[field].asString(),
                                                                            company_public_key);
            company_encrypted_data[field] = company_encrypted_message;
        }
        Assertions::assertValidDataFields(company_encrypted_data.getMemberNames());

        // Forwards the company encrypted data
        // OutputMessageClient.forwardCompanyEncryptedData(request_id, company_encrypted_data);

        // Forwards the private key
        // OutputMessageClient.forwardCompanyPrivateKey(request_id, string private_key);

    }else{
        // Forwards the error message
        // OutputMessageClient.forwardInvalidUserDataFields(request_id, invalid_fields);
    }
}