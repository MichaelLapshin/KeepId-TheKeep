/**
 * @filename: TaskManager.cpp
 * @description: Definition of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */

#include <thread>
#include <mutex>
#include <atomic>
#include <assert.h>

#include <jsoncpp/json/json.h>

#include "TaskManager.hpp"
#include "../key-manager/KeyManager.hpp"
#include "../data-fields/Assertions.cpp"

using namespace std;

/**
 * TaskManager::TaskManager()
 */
TaskManager::TaskManager(){
    is_running = false;
    loop_thread = false;
}

/**
 * TaskManager::~TaskManager()
 */
TaskManager::~TaskManager(){
    delete thread_obj;
}

/**
 * start
 */
void TaskManager::start(){
    loop_thread = true;
    thread_obj = new thread(TaskManager::workLoop, this);
    is_running = true;
}

/**
 * TaskManager::stop()
 */
void TaskManager::stop(){
    loop_thread = false;
    thread_obj->join();
    is_running = false;
}

/**
 * TaskManager::isRunning()
 */
bool TaskManager::isRunning(){
    return is_running;
}

/**
 * TaskManager::workLoop()
 */
void TaskManager::workLoop(atomic<bool> &loop_thread){
    while(loop_thread){
        /////////////////////////////////////////////
        ///  Poll and execute user-data updating  ///
        /////////////////////////////////////////////
        Json::Value data_update_json; // = MessageClient.PollFetchDataUpdate() // Contains user_id, request_id, encrypted_data_fields
        
        TaskManager::userDataUpdateTask(data_update_json);

        /////////////////////////////////////////////
        ///     Poll and execute data-request     ///
        /////////////////////////////////////////////
        const Json::Value data_request_input; // = MessageClient.fetchUserDataRequest() // Contains user_id, request_id, private_keys, public_keys
        TaskManager::userDataRequestTask(data_request_input);
    }
}

/**
 * TaskManager::userDataUpdateTask()
 */
void TaskManager::userDataUpdateTask(Json::Value data_update_input){
    Assertions::assertValidDataUpdate(data_update_input);

    // Constants
    const string &user_id = data_update_input[USER_ID].asString();
    const Json::Value &encrypted_data_fields = data_update_input[ENCRYPTED_DATA_FIELDS];

    // HolyCow.storeUserData(user_id, encrypted_data); 
}

/**
 * TaskManager::userDataRequestTask()
 */
void TaskManager::userDataRequestTask(Json::Value data_request_input){
        Assertions::assertValidDataRequest(data_request_input);

        // Constants
        const vector<string> &data_fields = data_request_input[PUBLIC_KEYS].getMemberNames();

        const string &user_id = data_request_input[USER_ID].asString();
        const string &request_id = data_request_input[REQUEST_ID].asString();
        const Json::Value &private_keys = data_request_input[PRIVATE_KEYS];
        const Json::Value &public_keys = data_request_input[PUBLIC_KEYS];
        
        // Fetch encrypted user data
        const Json::Value encrytped_data; // = HolyCow.fecthKeepUserData(user_id, data_fields);

        // Decrypt user data
        Json::Value decrypted_data{};
        for(const string &field : data_fields){
            string decrypted_message = KeyManager::decryptMessage(encrytped_data[field].asString(),
                                                                  private_keys[field].asString());
            decrypted_data[field] = decrypted_message;
        }
        Assertions::assertValidDataFields(decrypted_data.getMemberNames());

        // Reencrypts the data
        Json::Value reencrypted_data{};
        for(const string &field : data_fields){
            string reencrypted_message = KeyManager::encryptMessage(decrypted_data[field].asString(),
                                                                    public_keys[field].asString());
            reencrypted_data[field] = reencrypted_message;
        }
        Assertions::assertValidDataFields(reencrypted_data.getMemberNames());

        // Stores the reencrypted data
        Json::Value data_update_input;
        data_update_input[USER_ID] = user_id;
        data_update_input[ENCRYPTED_DATA_FIELDS] = reencrypted_data;
        TaskManager::userDataUpdateTask(data_update_input); // Sends user_id, encrypted_data_fields

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
