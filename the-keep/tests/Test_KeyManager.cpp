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

#include "../core/key-manager/KeyManager.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

/* NOTE: Since we are testing the static class KeyManager, 
 *       then each should be tested individually.
 */

/**
 * Initialize - Test that the KeyManager is properly initialized the first time,
 *              but correctly throws for any subsequent initialization attempts. 
 */
TEST(TestKeyManager, Initialize){
    CryptoWrapper_Cryptopp wrapper1, wrapper2, wrapper3;
    EXPECT_NO_THROW(KeyManager::initialize(&wrapper1));
    EXPECT_THROW(KeyManager::initialize(&wrapper2), runtime_error);
    EXPECT_THROW(KeyManager::initialize(&wrapper3), runtime_error);
}

/**
 * GetPublicKey - Test that the getPublicKey() method correctly
 *                returns the public key.
 */
TEST(TestKeyManager, GetPublicKey){
    // Intiliaze the KeyManager
    CryptoWrapper_Cryptopp wrapper;
    ASSERT_NO_THROW(KeyManager::initialize(&wrapper));

    // Obtains the public key from the file
    ifstream public_key_file {std::string("KeepPublicKey.dat")};
    std::string str_public_key;
    str_public_key.assign(std::istreambuf_iterator<char>(public_key_file),
                          std::istreambuf_iterator<char>());

    // Assert that the public key from the KeyManager matches that of the file
    EXPECT_EQ(KeyManager::getPublicKey(), str_public_key);
}

/**
 * ReadKeysFromStorage - Test that the KeyManager correctly read the keys.
 */
TEST(TestKeyManager, ReadKeysFromStorage){
    // Obtains the sample test keys from the tests folder
    ifstream in_public_key_file {std::string("./the-keep/tests/sample_test_keys/KeepPublicKey.test_dat")};
    std::string str_public_key;
    str_public_key.assign(std::istreambuf_iterator<char>(in_public_key_file),
                          std::istreambuf_iterator<char>());
    in_public_key_file.close();

    ifstream in_private_key_file {std::string("./the-keep/tests/sample_test_keys/KeepPrivateKey.test_dat")};
    std::string str_private_key;
    str_private_key.assign(std::istreambuf_iterator<char>(in_private_key_file),
                           std::istreambuf_iterator<char>());
    in_private_key_file.close();
    
    // Writes the keys into standard location
    ofstream out_public_key_file {std::string("KeepPublicKey.dat")};
    out_public_key_file << str_public_key;
    out_public_key_file.close();

    // Saves private key
    ofstream out_private_key_file {std::string("KeepPrivateKey.dat")};
    out_private_key_file << str_private_key;
    out_private_key_file.close();

    // Intiliaze the KeyManager (the KeyManager should read the keys from the .dat files)
    CryptoWrapper_Cryptopp wrapper;
    ASSERT_NO_THROW(KeyManager::initialize(&wrapper));

    // Assert that the public key from the KeyManager matches that of the file
    EXPECT_EQ(KeyManager::getPublicKey(), str_public_key);

    // To test the private key, we encrypt a message using the public key and 
    // decrypt it. A successfull encryption would imply that the private key works.
    std::string sample_message {"Hello world! This is a random test message."};
    std::string encrypted_message = KeyManager::encryptMessage(sample_message);
    std::string decrypted_message = KeyManager::decryptMessage(encrypted_message);
    EXPECT_EQ(sample_message, decrypted_message);
}

/**
 * EncryptDecryptMessageSimple - Test that a string can be encrypted
 *              and decrypted 
 */
TEST(TestKeyManager, EncryptDecryptMessageSimple){
    // Intiliaze the KeyManager
    CryptoWrapper_Cryptopp wrapper;
    ASSERT_NO_THROW(KeyManager::initialize(&wrapper));

    // Reencrypt message and assert that the message has been preserved.
    std::string sample_message {"Hello world! This is a simple sample test message."};
    std::string encrypted_message = KeyManager::encryptMessage(sample_message);
    std::string decrypted_message = KeyManager::decryptMessage(encrypted_message);
    EXPECT_EQ(sample_message, decrypted_message);
}

/**
 * EncryptDecryptMessageComplex - Test 
 */
TEST(TestKeyManager, EncryptDecryptMessageComplex){
    // Intiliaze the KeyManager
    CryptoWrapper_Cryptopp wrapper;
    ASSERT_NO_THROW(KeyManager::initialize(&wrapper));

    // Original messages
    std::string sample_msg_1 {"Hello world! This is the first sample message."};
    std::string sample_msg_2 {"Hello world! This is the second sample message."};
    ASSERT_NE(sample_msg_1, sample_msg_2);

    // Consecutive reencryption
    std::string consecutive_encr_1 = KeyManager::encryptMessage(sample_msg_1);
    std::string consecutive_decr_1 = KeyManager::decryptMessage(consecutive_encr_1);
    EXPECT_EQ(sample_msg_1, consecutive_decr_1);
    
    std::string consecutive_encr_2 = KeyManager::encryptMessage(sample_msg_2);
    std::string consecutive_decr_2 = KeyManager::decryptMessage(consecutive_encr_2);
    EXPECT_EQ(sample_msg_2, consecutive_decr_2);

    // Overlapping reencryption
    std::string overlapping_encr_1 = KeyManager::encryptMessage(sample_msg_1);
    std::string overlapping_encr_2 = KeyManager::encryptMessage(sample_msg_2);

    std::string overlapping_decr_1 = KeyManager::decryptMessage(overlapping_encr_1);
    std::string overlapping_decr_2 = KeyManager::decryptMessage(overlapping_encr_2);

    EXPECT_EQ(sample_msg_1, overlapping_decr_1);
    EXPECT_EQ(sample_msg_2, overlapping_decr_2);

    // Enclosed reencryption
    std::string enclosed_encr_1 = KeyManager::encryptMessage(sample_msg_1);
    std::string enclosed_encr_2 = KeyManager::encryptMessage(sample_msg_2);
    std::string enclosed_decr_2 = KeyManager::decryptMessage(enclosed_encr_2);
    std::string enclosed_decr_1 = KeyManager::decryptMessage(enclosed_encr_1);

    EXPECT_EQ(sample_msg_1, enclosed_decr_1);
    EXPECT_EQ(sample_msg_2, enclosed_decr_2);
}
