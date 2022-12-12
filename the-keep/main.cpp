
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

// threads and sleep
#include <unistd.h>
#include <thread>
#include <chrono>

#include "core/Logger.hpp"
#include "core/key-manager/KeyManager.hpp"
#include "core/task-manager/TaskManager.hpp"
#include "core/data-fields/Config.hpp"

#include "comms/KafkaDriver.hpp"
#include "comms/TheKeepDB.hpp"
#include "comms/CassandraDriver.hpp"
#include "comms/CommsConfig.hpp"

using namespace std;
using namespace thekeep;


int main(int argc, char *argv[]){
    // Starts the Keep
    spdlog::info("Initializing the Keep... ");  // to Console
    KeyManager::initializeKeepKeys();
    Config::initialize();
    KeepLogger::initialize();
    spdlog::info("SpdLog: TheKeep initialization has done.");

    DEBUG("test of the debug logger macro");
    KeepLogger::flash();

    // Development test --- TODO: remove this
/* * /
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
               DEBUG("tick: " + to_string(i) +  " -> " + messages.front());        
               messages.pop();
        }
    }
/ * */
    TheKeepDB *db = new CassandraDriver();
    db->connect(CASSANRDA_URL,"cassandra","cassandra");
    TheKeepRecord data = db->get(123,23);
    DEBUG("test: ");
    DEBUG(data.userid << " - " << data.fieldid << ": " << data.chip);
    delete db;
// * /

    TaskManager worker{};

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
                spdlog::error("The Keep must be stopped. Enter 'stop' to stop the Keep.");
            }
        }else{
            cerr << "Invalid command. Enter '--help' for command instructions." << endl;
        }
    }

    // Stops the Keep
    LOG("Uninitializing the Keep... ");
    Config::uninitialize();
    LOG("Uninitialization Has Done.");
    LOG("Exiting the program...");
    return 0;
}
