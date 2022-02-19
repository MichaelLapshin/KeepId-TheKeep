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

#include "TaskManager.hpp"

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
        // string data_update_json = ;
        
        // Poll and execute data-request
        // string data_request_json = ;
    }
}
