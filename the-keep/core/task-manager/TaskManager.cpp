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
    shared_resources = SharedResources();

    // Assertions
    assert(!std::is_trivially_copyable<SharedResources>::value);
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
    shared_resources.load().loop_thread = true;
    thread_obj = new thread(TaskManager::workLoop, this);
    is_running = true;
}

/**
 * TaskManager::stop()
 */
void TaskManager::stop(){
    shared_resources.load().loop_thread = false;
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
void TaskManager::workLoop(atomic<SharedResources> &sr){
    while(sr.load().loop_thread){
        // Poll and execute user-data updating
        // Json::Value data_update_json; // = MessageClient.PollFetchDataUpdate()
        
        // 

        // Poll and execute data-request
        Json::Value data_request_input; // = MessageClient.PollFetchDataRequest() // Contains user_id, request_id, private_keys
        

        // Fetch encrypted user data
        vector<string> data_fields = data_request_input.getMemberNames();
        vector<string> encrytped_data; // = MessageClient.FecthKeepData(user_id, data_fields);
        
        // Assertions
        assert(encrytped_data.size() == data_fields.size());
        
        // Fecth private keys from JSON
        Json::Value private_keys = Json.;
        

        // Decrypt user data
        vector<string> decrypted_data(data_fields.size());
        Json::Value data_request_output
        for(int i = 0; i < decrypted_data.size(); i++){
            decrypted_data[i] = KeyManager::decryptMessage(, );
        }

        assert() 
        Json::Value decrypted_data;

    }
}
