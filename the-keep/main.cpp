
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

// threads and sleep
#include <unistd.h>
#include <thread>
#include <chrono>

#include "core/key-manager/KeyManager.hpp"
#include "core/task-manager/TaskManager.hpp"
#include "core/data-fields/Config.hpp"

#include "comms/KafkaDriver.hpp"
#include "comms/TheKeepDB.hpp"
#include "comms/CassandraDriver.hpp"
#include "comms/CommsConfig.hpp"

using namespace std;
using namespace thekeep;

void initialize();
void uninitialize();

int main(int argc, char *argv[]){
    // Initializes the critical components of the Keep
    initialize();
    TaskManager worker{};

    // Development test 
/*
    unique_ptr<TheKeepMessaging> kd = make_unique<KafkaDriver>();
    kd->initialize("");
    kd->subscribe("keepid-tests");
    kd->send("keepid-tests","test-c++ 1235");
    kd->send("keepid-tests","test-c++ 123567");

    queue<string> messages;
    for (int i=0;i<100;i++) {
        sleep(1);
        messages = kd->receive("keepid-tests",100);
        while(!messages.empty())
        {
               cout << "tick: " + to_string(i) +  " -> " + messages.front() << endl;        
               messages.pop();
        }
    }

    TheKeepDB *db = new CassandraDriver();
    db->connect(CASSANRDA_URL,"cassandra","cassandra");
    TheKeepRecord data = db->get(123,23);
    cout << "test: ";
    cout << data.userid << " - " << data.fieldid << ": " << data.chip << std::endl;
    delete db;
*/

    // Starts the command line interface
    bool is_running = true;
    while(is_running){
        // Parses the a
        string input; 
        cin >> input;

        // Processes the input
        if(input == "--help"){
            cout << "--help   : Display help message." << endl;
            cout << "--start  : Start the Keep." << endl;
            cout << "--stop   : Stop the Keep." << endl;
            cout << "--exit   : Exit the program." << endl;
        }else if(input == "--start"){
            worker.start();
        }else if(input == "--stop"){
            worker.stop();
        }else if(input == "--exit"){
            if (!worker.isRunning()){
                is_running = false;
            }else{
                cerr << "The Keep must be stopped. Enter 'stop' to stop the Keep." << endl;
            }
        }else{
            cerr << "Invalid command. Enter '--help' for command instructions." << endl;
        }
    }

    uninitialize();
    cout << "Exiting the program..." << endl;
    return 0;
}

/**
 * initialize()
 * @brief Initializes all components used in running the Keep.
 */
void initialize(){
    cout << "Initializing the Keep... ";
    Config::initialize();
    KeyManager::initialize();
    cout << "Done." << endl;
}

/**
 * uninitialize()
 * @brief Uninitializes all components used in running the Keep.
 */
void uninitialize(){
    cout << "Uninitializing the Keep... ";
    KeyManager::uninitialize();
    Config::uninitialize();
    cout << "Done." << endl;
}