/**
 * @filename: TaskManager.hpp
 * @description: Declaration of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */

#pragma once
#include <thread>
#include <atomic>
#include <jsoncpp/json/json.h>

using namespace std;

class TaskManager {
    public:
        /**
         * TaskManager::TaskManager()
         * @brief The task manager's constructor.
         */
        TaskManager();

        /**
         * TaskManager::TaskManager()
         * @brief The task manager's destructor.
         */
        ~TaskManager();

        /**
         * TaskManager::start()
         * @brief Starts the task manager.
         */
        void start();
        
        /**
         * TaskManager::stop()
         * @brief Stops the task manager.
         */
        void stop();

        /**
         * TaskManager::isRunning()
         * @brief A getter to indicate if the task
         *        manager is running.
         * @return The running status.
         */
        bool isRunning();
    protected:
    private:       
        /**
         * TaskManager::workLoop()
         * @brief The method that would be run whenever
         *        the task manager is started.
         */
        static void workLoop(atomic<bool> &loop_thread);

        /**
         * TaskManager::dataUpdateTask()
         * @brief Performs the user data database update task.
         * 
         * @param data_update_input The data to update the database with.
         */
        static void userDataUpdateTask(Json::Value data_update_input);

        /**
         * TaskManager::userDataRequestTask()
         * @brief Performs the user data request task.
         * 
         * @param data_request_input The data request input Json.
         */
        static void userDataRequestTask(Json::Value data_request_input);

        // Variables
        bool is_running = false;
        atomic<bool> loop_thread;
        thread *thread_obj;
};
