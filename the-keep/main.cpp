
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "core/key-manager/KeyManager.hpp"
#include "core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"
#include "core/task-manager/TaskManager.hpp"
#include "core/data-fields/Config.hpp"

using namespace std;

int main(int argc, char *argv[]){
    // Initializes the critical components of the Keep
    Config::initialize();
    CryptoWrapper_Cryptopp wrapper;
    KeyManager::initialize(&wrapper);
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
                cerr << "The Keep must be stopped. Enter 'stop' to stop the Keep." << endl;
            }
        }else{
            cerr << "Invalid command. Enter '--help' for command instructions." << endl;
        }
    }

    cout << "Exiting the program..." << endl;
    Config::deinitialize();
    return 0;
}
