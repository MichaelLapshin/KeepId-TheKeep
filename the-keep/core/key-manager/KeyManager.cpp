/**
 * @filename: KeyManager.cpp
 * @description: The static class definition for the Keep's key manager.
 * @author: KeepId
 * @date: February 3, 2022
 */

#ifndef KEY_MANAGER
#define KEY_MANAGER

#include "KeyManager.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

/**
 * KeyManager::initialize()
 */
void KeyManager::initialize(CryptoWrapper *wrapper){
    if (KeyManager::initialized_){
        throw runtime_error("Attempted to initialize the Key Manager a second time.");
    }

    // House-keeping procedure
    KeyManager::crypto_wrapper_ = wrapper;
    KeyManager::initialized_ = true;

    if (areKeysInStorage()){
        // Reads keys from the files
        readKeysFromStorage();
    }else{
        // Generates and stores the keys
        pair<string, string> key_pair = generateKeyPair();
        KeyManager::public_key_ = key_pair.first;
        KeyManager::private_key_ = key_pair.second;

        writeKeysToStorage();
    }
}

/*
 * KeyManager::getPublicKey()
 */
string KeyManager::getPublicKey(){
    return KeyManager::public_key_;
}

/**
 * KeyManager::encryptMessage()
 */
string KeyManager::encryptMessage(string message, string str_publ_key){
    return KeyManager::crypto_wrapper_->encryptRSAMessage( 
                message,
                str_publ_key
            );
}

/**
 * KeyManager::decryptMessage()
 */
string KeyManager::decryptMessage(string message, string str_priv_key){
    return KeyManager::crypto_wrapper_->decryptRSAMessage(
                message,
                str_priv_key
            );
}

/**
 * KeyManager::generateKeyPair()
 */
pair<string, string> KeyManager::generateKeyPair(){
    if (!KeyManager::initialize){
        throw runtime_error("The KeyManager was not initilaized.");
    }

    return KeyManager::crypto_wrapper_->generateRSAKeyPair();
}

/**
 * KeyManager::areKeysInStrage()
 */
bool KeyManager::areKeysInStorage(){
    return filesystem::exists(KeyManager::kPublicKeyFile)
        && filesystem::exists(KeyManager::kPrivateKeyFile);
}

/**
 * KeyManager::writeKeysToStorage()
 */
void KeyManager::writeKeysToStorage(){
    // Saves public key
    ofstream public_key_file {KeyManager::kPublicKeyFile};
    public_key_file << KeyManager::public_key_;
    public_key_file.close();

    // Saves private key
    ofstream private_key_file {KeyManager::kPrivateKeyFile};
    private_key_file << KeyManager::private_key_;
    private_key_file.close();
}

/**
 * KeyManager::readKeysFromStorage()
 */
void KeyManager::readKeysFromStorage(){
    // Read public key
    ifstream public_key_file {KeyManager::kPublicKeyFile};
    KeyManager::public_key_.assign(
            istreambuf_iterator<char>(public_key_file),
            istreambuf_iterator<char>());
    public_key_file.close();

    

    // Read private key
    ifstream private_key_file {KeyManager::kPrivateKeyFile};
    KeyManager::private_key_.assign(
            istreambuf_iterator<char>(private_key_file),
            istreambuf_iterator<char>());
    private_key_file.close();
}

#endif