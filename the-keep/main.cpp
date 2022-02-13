
#include <cstdlib>
#include <iostream>

#include "core/key-manager/KeyManager.hpp"
#include "core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std;

void startWorkerLoop();

int main(){
    cout << "Hello the Keep!" << endl;

    startWorkerLoop();

    return 0;
}

void startWorkerLoop(){
    // Creates cryptography wrapper object
    CryptoWrapper_Cryptopp wrapper;
    
    cout << "YEsssS" << endl;
    
    // Sets the cryptography library wrapper
    KeyManager::initialize(&wrapper);
    cout << "Initialized." << endl;

    string raw_msg = "Hello world!";
    string encoded = KeyManager::encryptMessage(raw_msg); 
    cout << "Done encrypting" << endl;
    string decoded = KeyManager::decryptMessage(encoded); 

    cout << raw_msg << endl;
    cout << encoded << endl;
    cout << decoded << endl;

    // Creates and starts the worker
    // TaskWorker worker {};
    // worker.startLoop();
}