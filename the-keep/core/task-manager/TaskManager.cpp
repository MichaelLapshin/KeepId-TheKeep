/**
 * @filename: TaskManager.cpp
 * @description: Definition of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */
// ?? #include <functional>

#include "TaskManager.hpp"
#include "TaskLogic.hpp"  

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
    if (!is_running){  // guard
        loop_thread = true;
        thread_obj = new thread(workLoop, ref(this->loop_thread));
        is_running = true;
    }
}

/**
 * TaskManager::stop()
 */
void TaskManager::stop(){
    if (is_running){ // guard
        loop_thread = false;
        thread_obj->join();
        // TODO: Delete thread_obj, or change to unique_ptr<>
        is_running = false;
    }
}

/**
 * TaskManager::isRunning()
 */
bool TaskManager::isRunning(){
    return is_running;
}
