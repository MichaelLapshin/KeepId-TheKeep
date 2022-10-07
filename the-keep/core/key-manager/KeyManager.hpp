/**
 * @filename: KeyManager.hpp
 * @description: The static class declaration for the Keep's key manager.
 * @author: KeepId
 * @date: February 3, 2022
 */

#pragma once

#include <string>
#include <unique_ptr>

#include "../cryptography-wrappers/CryptoWrapper.hpp"

using namespace std;

class KeyManager {
    public:

        /**
         * KeyManager::initializeKeepKeys()
         * @brief Generates a public/private key pair and saves them as the Keep keys.
         */
        static void initializeKeepKeys();

        /**
         * KeyManager::generateKeyPair()
         * @brief Using crypto-libraries, generates an 2048-bit asymmetric key pair.
         * 
         * @return Returns a pair of asymmetric cryptographic keys. pair<str_public_key, str_private_key>
         */
        static pair<string, string> generateKeyPair();

        /**
         * KeyManager::getPublicKey()
         * @brief A simple getter for retrieving the public key.
         * 
         * @return The public key in DER format
         */
        static string getPublicKey();

        /**
         * KeyManager::encryptMessage()
         * @brief Allows external members to encrypt their data.
         * 
         * @param[in] message Message to encrypt.
         */
        static string encryptMessage(string message, string str_publ_key = KeyManager::public_key_);

        /**
         * KeyManager::decryptMessage()
         * @brief Allows external members to decrypt their data.
         * 
         * @param[in] message Message to decrypt.
         */
        static string decryptMessage(string message, string str_priv_key = KeyManager::private_key_);
    
        /**
         * KeyManager::validatePublicKey()
         * @brief Validates the given public key.
         * 
         * @param[in] public_key The key to validate.
         * 
         * @return True if the key is valid, otherwise false.
         */
        static bool validatePublicKey(string public_key);

        /**
         * KeyManager::validatePrivateKey()
         * @brief Validates the given private key.
         * 
         * @param[in] private_key The key to validate.
         * 
         * @return True if the key is valid, otherwise false.
         */
        static bool validatePrivateKey(string private_key);
    private:
        // RSA key pair variables in DER format
        inline static string public_key_ = "";
        inline static string private_key_ = "";

        // Manager variables
        inline static std::unique_ptr<CryptoWrapper> crypto_wrapper_ = make_unique<CryptoWrapper_Cryptopp>();
};
