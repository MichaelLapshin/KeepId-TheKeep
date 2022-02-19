/**
 * @filename: TaskManager.cpp
 * @description: Declaration of the Task Manager in charge of fetching 
 *               and executing the Keep' tasks.
 * @author: KeepId 
 * @date: February 19, 2022
 */

class TaskManager {
    public:
        TaskManager();
        void start();
        void stop();
        bool isRunning();
    protected:
    private:
        bool is_running = false;
};
