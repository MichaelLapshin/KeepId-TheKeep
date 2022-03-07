/**
 * @filename: TaskManager.hpp
 * @description: Declaration of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */

#include <thread>
#include <atomic>

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
        // Variables
        bool is_running = false;
        atomic<bool> loop_thread;
        thread *thread_obj;
};
