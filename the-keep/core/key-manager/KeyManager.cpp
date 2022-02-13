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
    if (!KeyManager::initialized_){
        // House-keeping procedure
        KeyManager::crypto_wrapper_ = wrapper;
        KeyManager::initialized_ = true;

        if (areKeysInStorage()){
            // Reads keys from the files
            readKeysFromStorage();
        }else{
            // Generates and stores the keys
            generateKeyPair();
            writeKeysToStorage();
        }

    }else{
        throw runtime_error(
            "Attempted to initialize the Key Manager a second time.");
    }
}

/*
 * KeyManager::getPublicKey()
 */
string KeyManager::getPublicKey(){
    return public_key_;
}

/**
 * KeyManager::encryptMessage()
 */
string KeyManager::encryptMessage(string message, string str_publ_key){
    return KeyManager::crypto_wrapper_->encryptRSAMessage(
                str_publ_key, 
                message
            );
}

/**
 * KeyManager::decryptMessage()
 */
string KeyManager::decryptMessage(string message, string str_priv_key){
    return KeyManager::crypto_wrapper_->decryptRSAMessage(
                KeyManager::private_key_, 
                message
            );
}

/**
 * KeyManager::generateKeyPair()
 */
void KeyManager::generateKeyPair(){
    pair<string, string> key_pair = KeyManager::crypto_wrapper_->generateRSAKeyPair();
    KeyManager::public_key_ = key_pair.first;
    KeyManager::private_key_ = key_pair.second;
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
    std::ofstream public_key_file {KeyManager::kPublicKeyFile};
    public_key_file << KeyManager::public_key_;
    public_key_file.close();

    // Saves private key
    std::ofstream private_key_file {KeyManager::kPrivateKeyFile};
    private_key_file << KeyManager::private_key_;
    private_key_file.close();
}

/**
 * KeyManager::readKeysFromStorage()
 */
void KeyManager::readKeysFromStorage(){
    // Read public key
    ifstream public_key_file {KeyManager::kPublicKeyFile};
    getline(public_key_file, KeyManager::public_key_);
    public_key_file.close();

    // Read private key
    ifstream private_key_file {KeyManager::kPrivateKeyFile};
    getline(private_key_file, KeyManager::private_key_);
    private_key_file.close();
}

#endif