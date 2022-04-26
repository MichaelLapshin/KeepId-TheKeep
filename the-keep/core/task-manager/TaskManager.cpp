/**
 * @filename: TaskManager.cpp
 * @description: Definition of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */

#include <functional>
#include <thread>
#include <atomic>
#include <assert.h>

#include <jsoncpp/json/json.h>

#include "TaskManager.hpp"
#include "TaskLogic.cpp"
#include "../key-manager/KeyManager.hpp"
#include "../data-fields/Assertions.hpp"

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
 * TaskManager::start()
 */
void TaskManager::start(){
    loop_thread = true;
    thread_obj = new thread(workLoop, ref(this->loop_thread));
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
