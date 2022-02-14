
#include <cstdlib>
#include <iostream>

#include "core/key-manager/KeyManager.hpp"
#include "core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std;

void startWorkerLoop();

int main(){
    startWorkerLoop();
    return 0;
}

void startWorkerLoop(){
    // Creates cryptography wrapper object
    CryptoWrapper_Cryptopp wrapper;
        
    // Sets the cryptography library wrapper
    KeyManager::initialize(&wrapper);

    cout << "Public Key: " << endl;
    cout << KeyManager::getPublicKey() << endl;
    string raw_msg = "Hello world! This is a raw message.";
    string encoded = KeyManager::encryptMessage(raw_msg); 
    string decoded = KeyManager::decryptMessage(encoded); 

    cout << endl << "=== RESULT === " << endl;
    cout << "Original message: " << raw_msg << endl;
    cout << "Encoded message: " << encoded << endl;
    cout << "Decoded message: " << decoded << endl;

    // Creates and starts the worker
    // TaskWorker worker {};
    // worker.startLoop();
}