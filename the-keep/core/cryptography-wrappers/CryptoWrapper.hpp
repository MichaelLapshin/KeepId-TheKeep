/**
 * @filename: CryptoWrapper.hpp
 * @description: The declaration of the abstract cryptography wrapper class for KeepId.
 * @author: KeepId
 * @date: March 27, 2022
 */

#pragma once

#include <string>
#include <utility>

using namespace std;

class CryptoWrapper {
    public:
        /**
         * generateRSAKeyPair()
         * @brief Generates an RSA 2048-bit cryptography public-private key pair.
         * 
         * @return A pair of strings consisting of a public and private key.
         */
        virtual pair<string, string> generateRSAKeyPair() const = 0;

        /**
         * encryptRSAMessage()
         * @brief Encrypt a message given a public key and the string message.
         * 
         * @param[in] message      The message to encrypt.
         * @param[in] str_publ_key The 2048-bit RSA public-key string.
         * 
         * @return The encrypted message using the 2048-bit RSA public key.
         */
        virtual string encryptRSAMessage(string message, string str_publ_key) const = 0;

        /**
         * decryptRSAMessage()
         * @brief Decrypt a message given a private key and the string message.
         * 
         * @param[in] message      The message to encrypt.
         * @param[in] str_publ_key The 2048-bit RSA private-key string.
         * 
         * @return The decrypted message using the 2048-bit RSA public key.
         */
        virtual string decryptRSAMessage(string message, string str_priv_key) const = 0;

        /**
         * validatePublicKey()
         * @brief A function used to validate a public-key.
         * 
         * @param[in] public_key The 2048-bit public key to validate.
         * 
         * @return True if the public-key is valid, otherwise false.
         */
        virtual bool validatePublicKey(string public_key) const = 0;

        /**
         * validatePrivateKey()
         * @brief A function used to validate a private-key.
         * 
         * @param[in] private_key The 2048-bit private key to validate.
         * 
         * @return True if the private-key is valid, otherwise false.
         */
        virtual bool validatePrivateKey(string private_key) const = 0;
        virtual ~CryptoWrapper() {}
    protected:
        const int ENCRYPTION_KEY_BIT_SIZE = 2048;
    private:
};
