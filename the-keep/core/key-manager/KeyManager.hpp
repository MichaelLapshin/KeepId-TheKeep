/**
 * @filename: KeyManager.hpp
 * @description: The static class declaration for the Keep's key manager.
 * @author: KeepId
 * @date: February 3, 2022
 */

#include <string>

#include "../cryptography-wrappers/CryptoWrapper.hpp"

using namespace std;

class KeyManager {
    public:

        /**
         * KeyManager::initialize()
         * @brief Reads the public and private keys from the designated file or 
         *          generates and stores the keys if they do not already exist.
         * @param wrapper The cryptogrophy object with normalized functions.
         */
        static void initialize(CryptoWrapper *wrapper);

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
         * @param message Message to encrypt.
         */
        static string encryptMessage(string message, string str_publ_key = KeyManager::public_key_);

        /**
         * KeyManager::decryptMessage()
         * @brief Allows external members to decrypt their data.
         * @param message Message to decrypt.
         */
        static string decryptMessage(string message, string str_priv_key = KeyManager::private_key_);
    protected:
    private:
        /**
         * KeyManager::generateKeyPair()
         * @brief Using crypto-libraries, generates an 2048-bit asymmetric key pair.
         * @return Returns a pair of asymmetric cryptographic keys.
         */
        static void generateKeyPair();

        /**
         * KeyManager::areKeysInStorage()
         * @brief Attempts to identify the public and private key within
         *          the predefined key storage location.
         */
        static bool areKeysInStorage(string public_key_file_name = KeyManager::kPublicKeyFile, 
                                     string private_key_file_name = KeyManager::kPrivateKeyFile);

        /**
         * KeyManager::writeKeysToStorage()
         * @brief Uses the keys stored as private variables and writes
         *          them into the predefined storage location.
         */
        static void writeKeysToStorage(string public_key_file_name = KeyManager::kPublicKeyFile, 
                                       string private_key_file_name = KeyManager::kPrivateKeyFile);

        /**
         * KeyManager::readKeysFromStorage()
         * @brief Reads the keys from the predefined storage location 
         *          and write the keys into the private variables.
         * @return A public and private key in the form of a pair (private, public).
         */
        static void readKeysFromStorage(string public_key_file_name = KeyManager::kPublicKeyFile, 
                                        string private_key_file_name = KeyManager::kPrivateKeyFile);

        // File constants
        inline static const string kPublicKeyFile = "KeepPublicKey.dat";
        inline static const string kPrivateKeyFile = "KeepPrivateKey.dat";

        // RSA key pair variables in DER format
        inline static string public_key_ = "";
        inline static string private_key_ = "";

        // Manager variables
        inline static CryptoWrapper* crypto_wrapper_ = nullptr;
        inline static bool initialized_ = false;
};
