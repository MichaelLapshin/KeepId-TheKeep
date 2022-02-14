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
void KeyManager::generateKeyPair(){
    pair<string, string> key_pair = KeyManager::crypto_wrapper_->generateRSAKeyPair();
    KeyManager::public_key_ = key_pair.first;
    KeyManager::private_key_ = key_pair.second;
}

/**
 * KeyManager::areKeysInStrage()
 */
bool KeyManager::areKeysInStorage(string public_key_file_name, 
                                  string private_key_file_name){
    return filesystem::exists(public_key_file_name)
        && filesystem::exists(private_key_file_name);
}

/**
 * KeyManager::writeKeysToStorage()
 */
void KeyManager::writeKeysToStorage(string public_key_file_name, 
                                    string private_key_file_name){
    // Saves public key
    std::ofstream public_key_file {public_key_file_name};
    public_key_file << KeyManager::public_key_;
    public_key_file.close();

    // Saves private key
    std::ofstream private_key_file {private_key_file_name};
    private_key_file << KeyManager::private_key_;
    private_key_file.close();
}

/**
 * KeyManager::readKeysFromStorage()
 */
void KeyManager::readKeysFromStorage(string public_key_file_name, 
                                     string private_key_file_name){
    // Read public key
    ifstream public_key_file {public_key_file_name};
    KeyManager::public_key_.assign(
            std::istreambuf_iterator<char>(public_key_file),
            std::istreambuf_iterator<char>());
    public_key_file.close();

    

    // Read private key
    ifstream private_key_file {private_key_file_name};
    KeyManager::private_key_.assign(
            std::istreambuf_iterator<char>(private_key_file),
            std::istreambuf_iterator<char>());
    private_key_file.close();
}

#endif