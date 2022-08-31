/**
 * @filename: KeyManager.cpp
 * @description: The static class definition for the Keep's key manager.
 * @author: KeepId
 * @date: February 3, 2022
 */

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "KeyManager.hpp"
#include "../cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std;

/**
 * KeyManager::initialize()
 */
void KeyManager::initialize(){
    if (KeyManager::initialized_){
        throw runtime_error("Attempted to initialize the Key Manager a second time.");
    }

    // Creates new cryptography object
    KeyManager::crypto_wrapper_ = new CryptoWrapper_Cryptopp();

    // Fills the private and public key variables
    if (areKeysInStorage()){
        // Reads keys from the files
        readKeysFromStorage();
    }else{
        // Generates and stores the keys
        KeyManager::initialized_ = true; // note: this is redundant but required by generateKeyPair() TODO: check logic
        pair<string, string> key_pair = generateKeyPair();
        KeyManager::public_key_ = key_pair.first;
        KeyManager::private_key_ = key_pair.second;

        writeKeysToStorage();
    }

    KeyManager::initialized_ = true;
}

/**
 * KeyManager::uninitialize()
 */
void KeyManager::uninitialize(){
    if (!KeyManager::initialized_){
        throw runtime_error("Attempted to uninitialize the Key Manager when it was never initialized.");
    }

    delete KeyManager::crypto_wrapper_;
    KeyManager::initialized_ = false;
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
 * KeyManager::validatePublicKey()
 */
bool KeyManager::validatePublicKey(string public_key){
    return KeyManager::crypto_wrapper_->validatePublicKey(public_key);
}

/**
 * KeyManager::validatePrivateKey()
 */
bool KeyManager::validatePrivateKey(string private_key){
    return KeyManager::crypto_wrapper_->validatePrivateKey(private_key);
}

/**
 * KeyManager::generateKeyPair()
 */
pair<string, string> KeyManager::generateKeyPair(){
    // TODO: check logic since this function is called during initialization before it's completed
    if (!KeyManager::initialized_){
        throw runtime_error("The KeyManager was not initilaized.");
    }

    return KeyManager::crypto_wrapper_->generateRSAKeyPair();
}

/**
 * KeyManager::areKeysInStrage()
 */
bool KeyManager::areKeysInStorage(){
    return filesystem::exists(KeyManager::PUBLIC_KEY_FILE)
        && filesystem::exists(KeyManager::PRIVATE_KEY_FILE);
}

/**
 * KeyManager::writeKeysToStorage()
 */
void KeyManager::writeKeysToStorage(){
    // Saves public key
    ofstream public_key_file {KeyManager::PUBLIC_KEY_FILE};
    public_key_file << KeyManager::public_key_;
    public_key_file.close();

    // Saves private key
    ofstream private_key_file {KeyManager::PRIVATE_KEY_FILE};
    private_key_file << KeyManager::private_key_;
    private_key_file.close();
}

/**
 * KeyManager::readKeysFromStorage()
 */
void KeyManager::readKeysFromStorage(){
    // Read public key
    ifstream public_key_file {KeyManager::PUBLIC_KEY_FILE};
    KeyManager::public_key_.assign(
            istreambuf_iterator<char>(public_key_file),
            istreambuf_iterator<char>());
    public_key_file.close();

    

    // Read private key
    ifstream private_key_file {KeyManager::PRIVATE_KEY_FILE};
    KeyManager::private_key_.assign(
            istreambuf_iterator<char>(private_key_file),
            istreambuf_iterator<char>());
    private_key_file.close();
}
