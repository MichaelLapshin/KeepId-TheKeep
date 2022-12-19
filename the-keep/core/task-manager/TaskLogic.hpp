/**
 * @filename: TaskLogic.hpp
 * @description: Declaration for the logic tasks' functions
 * @author: KeepId  {IL}
 * @date: December 11, 2022
 */
#pragma once
#include <atomic>
#include <string>

// Function declaration
void workLoop(const std::atomic<bool> &loop_thread);
void userDataUpdateTask(const std::string& data_update_input);
void userDataRequestTask(const std::string& data_request_input);
