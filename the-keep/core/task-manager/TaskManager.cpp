/**
 * @filename: TaskManager.cpp
 * @description: Definition of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */

#include <thread>

#include "TaskManager.hpp"

/**
 * TaskManager::TaskManager()
 */
TaskManager::TaskManager(){
    is_running = false;
}

/**
 * start
 */
void TaskManager::start(){
    is_running = true;
}

/**
 * TaskManager::stop()
 */
void TaskManager::stop(){
    is_running = false;
}

/**
 * TaskManager::isRunning()
 */
bool TaskManager::isRunning(){
    return is_running;
}
