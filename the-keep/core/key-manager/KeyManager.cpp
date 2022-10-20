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
#include "core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std;

/**
 * KeyManager::initializeKeepKeys()
 */
void KeyManager::initializeKeepKeys(){
    pair<string, string> key_pair = generateKeyPair();
    KeyManager::public_key_ = key_pair.first;
    KeyManager::private_key_ = key_pair.second;
}

/**
 * KeyManager::generateKeyPair()
 */
pair<string, string> KeyManager::generateKeyPair(){
    return KeyManager::crypto_wrapper_->generateRSAKeyPair();
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
