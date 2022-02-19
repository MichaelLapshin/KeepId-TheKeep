/**
 * @filename: TaskManager.cpp
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
        /**
         * @class SharedResources
         * @brief An atomically used class for sharing
         *        resources across threads.
         */
        class SharedResources{
            public:
                SharedResources();
                ~SharedResources();
                bool loop_thread = false;
            protected:
            private:
        };
        
        /**
         * TaskManager::workLoop()
         * @brief The method that would be run whenever
         *        the task manager is started.
         */
        static void workLoop(atomic<SharedResources> &shared_resources);

        // Variables
        bool is_running = false;
        atomic<SharedResources> shared_resources;
        thread *thread_obj;
};
