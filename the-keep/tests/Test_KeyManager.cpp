/**
 * @filename: Test_KeyManager.cpp
 * @description: To test the KeyManager static class.
 * @author: KeepId
 * @date: February 13, 2022
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include "test_common.hpp"
#include "../core/key-manager/KeyManager.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std;

/* NOTE: Since we are testing the static class KeyManager, 
 *       then each should be tested individually.
 */

/**
 * Initialize - Test that the KeyManager is properly initialized the first time,
 *              but correctly throws for any subsequent initialization attempts.
 *              Test that the KeyManager correctly uninitializes itself.
 */
TEST(TestKeyManager, InitializeUninitialize){
    // Tests the Key Manager's initialization
    EXPECT_NO_THROW(KeyManager::initialize());
    EXPECT_THROW(KeyManager::initialize(), runtime_error);
    EXPECT_THROW(KeyManager::initialize(), runtime_error);

    // Tests the Key Manager's uninitialization
    EXPECT_NO_THROW(KeyManager::uninitialize());
    EXPECT_THROW(KeyManager::uninitialize(), runtime_error);
}

/**
 * GetPublicKey - Test that the getPublicKey() method correctly
 *                returns the public key.
 */
TEST(TestKeyManager, GetPublicKey){
    // Intiliaze the KeyManager
    ASSERT_NO_THROW(KeyManager::initialize());

    // Obtains the public key from the file
    string str_public_key = readFile("KeepPublicKey.dat");

    // Assert that the public key from the KeyManager matches that of the file
    EXPECT_EQ(KeyManager::getPublicKey(), str_public_key);

    // Resets the Key Manager
    EXPECT_NO_THROW(KeyManager::uninitialize());
}

/**
 * ReadKeysFromStorage - Test that the KeyManager correctly read the keys.
 */
TEST(TestKeyManager, ReadKeysFromStorage){
    // Copies sample keys from sample folder into standard location
    copyFile("the-keep/tests/sample_test_keys/KeepPublicKey.test_dat", "KeepPublicKey.dat");
    copyFile("the-keep/tests/sample_test_keys/KeepPrivateKey.test_dat", "KeepPrivateKey.dat");

    // Intiliaze the KeyManager (the KeyManager should read the keys from the .dat files)
    ASSERT_NO_THROW(KeyManager::initialize());

    // Assert that the public key from the KeyManager matches that of the file
    std::string str_public_key = readFile("./the-keep/tests/sample_test_keys/KeepPublicKey.test_dat");
    EXPECT_EQ(KeyManager::getPublicKey(), str_public_key);

    // To test the private key, we encrypt a message using the public key and 
    // decrypt it. A successfull encryption would imply that the private key works.
    string sample_message {"Hello world! This is a random test message."};
    string encrypted_message = KeyManager::encryptMessage(sample_message);
    string decrypted_message = KeyManager::decryptMessage(encrypted_message);
    EXPECT_EQ(sample_message, decrypted_message);

    // Resets the Key Manager
    EXPECT_NO_THROW(KeyManager::uninitialize());
}

/**
 * EncryptDecryptMessageSimple - Test that a string can be encrypted and decrypted. 
 */
TEST(TestKeyManager, EncryptDecryptMessageSimple){
    // Intiliaze the KeyManager
    ASSERT_NO_THROW(KeyManager::initialize());

    // Reencrypt message and assert that the message has been preserved.
    string sample_message {"Hello world! This is a simple sample test message."};
    string encrypted_message = KeyManager::encryptMessage(sample_message);
    string decrypted_message = KeyManager::decryptMessage(encrypted_message);
    EXPECT_EQ(sample_message, decrypted_message);

    // Resets the Key Manager
    EXPECT_NO_THROW(KeyManager::uninitialize());
}

/**
 * EncryptDecryptMessageComplex - Test that  a string can be encrypted and decrypted
 *                                in more complex ways.  
 */
TEST(TestKeyManager, EncryptDecryptMessageComplex){
    // Intiliaze the KeyManager
    ASSERT_NO_THROW(KeyManager::initialize());

    // Original messages
    string sample_msg_1 {"Hello world! This is the first sample message."};
    string sample_msg_2 {"Hello world! This is the second sample message."};
    ASSERT_NE(sample_msg_1, sample_msg_2);

    // Consecutive reencryption
    string consecutive_encr_1 = KeyManager::encryptMessage(sample_msg_1);
    string consecutive_decr_1 = KeyManager::decryptMessage(consecutive_encr_1);
    EXPECT_EQ(sample_msg_1, consecutive_decr_1);
    
    string consecutive_encr_2 = KeyManager::encryptMessage(sample_msg_2);
    string consecutive_decr_2 = KeyManager::decryptMessage(consecutive_encr_2);
    EXPECT_EQ(sample_msg_2, consecutive_decr_2);

    // Overlapping reencryption
    string overlapping_encr_1 = KeyManager::encryptMessage(sample_msg_1);
    string overlapping_encr_2 = KeyManager::encryptMessage(sample_msg_2);

    string overlapping_decr_1 = KeyManager::decryptMessage(overlapping_encr_1);
    string overlapping_decr_2 = KeyManager::decryptMessage(overlapping_encr_2);

    EXPECT_EQ(sample_msg_1, overlapping_decr_1);
    EXPECT_EQ(sample_msg_2, overlapping_decr_2);

    // Enclosed reencryption
    string enclosed_encr_1 = KeyManager::encryptMessage(sample_msg_1);
    string enclosed_encr_2 = KeyManager::encryptMessage(sample_msg_2);
    string enclosed_decr_2 = KeyManager::decryptMessage(enclosed_encr_2);
    string enclosed_decr_1 = KeyManager::decryptMessage(enclosed_encr_1);

    EXPECT_EQ(sample_msg_1, enclosed_decr_1);
    EXPECT_EQ(sample_msg_2, enclosed_decr_2);

    // Resets the Key Manager
    EXPECT_NO_THROW(KeyManager::uninitialize());
}
