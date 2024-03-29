/**
 * @filename: Test_CryptoWrapper_Cryptopp.cpp
 * @description: To test the crypto++ implementation of the CryptoWrapper for KeepId.
 * @author: KeepId
 * @date: March 27, 2022
 */

#include <string>

#include <gtest/gtest.h>

#include <crypto++/rsa.h>
#include <crypto++/osrng.h>

#include "test_common.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std; 
using namespace CryptoPP;

/**
 * GenerateRSAKeyPairSimple - Test that valid keys can be generated
 *                            with the generateRSAKeyPair() method.
 */
TEST(TestCryptoWrapper_CryptoPP, GenerateRSAKeyPairSimple){
    CryptoWrapper_Cryptopp wrapper;

    // Generates and retrieves the keys
    pair<string, string> key_pair = wrapper.generateRSAKeyPair();
    string str_public_key = key_pair.first;
    string str_private_key = key_pair.second;

    // Create public key object
    RSA::PublicKey public_key;
    StringSource ss_publ_key(str_public_key, true);
    public_key.BERDecode(ss_publ_key);

    // Create private key object
    RSA::PrivateKey private_key;
    StringSource ss_priv_key(str_private_key, true);
    private_key.BERDecode(ss_priv_key);

    // Validate the keys
    AutoSeededRandomPool random_gen;
    public_key.Validate(random_gen, 3); // 3 = highest levels of checks, https://www.cryptopp.com/docs/ref/class_r_s_a_function.html#a2c43e097f0525db01c15bb53d80c2bea
    private_key.Validate(random_gen, 3); // 3 = highest levels of checks, https://www.cryptopp.com/docs/ref/class_r_s_a_function.html#a2c43e097f0525db01c15bb53d80c2bea
}

/**
 * EncryptDecryptMessageSimple - Test a simple case of encrypting and
 *      decrypting a string using the crypto++ wrapper implementation.
 */
TEST(TestCryptoWrapper_CryptoPP, EncryptDecryptMessageSimple){
    CryptoWrapper_Cryptopp wrapper;

    // Generates and retrieves the keys
    pair<string, string> key_pair = wrapper.generateRSAKeyPair();
    string str_public_key = key_pair.first;
    string str_private_key = key_pair.second;

    // Message details
    string sample_message {"Hello world! This is a simple sample test message."};
    string encrypted_message = wrapper.encryptRSAMessage(sample_message, str_public_key);
    string decrypted_message = wrapper.decryptRSAMessage(encrypted_message, str_private_key);
    EXPECT_EQ(sample_message, decrypted_message);
}

/**
 * EncryptDecryptMessageComplex - Test a complex case of encrypting and
 *         decrypting strings within the crypto++ wrapper implementation.
 */
TEST(TestCryptoWrapper_CryptoPP, EncryptDecryptMessageComplex){
    CryptoWrapper_Cryptopp wrapper;

    // Generates and retrieves the keys
    pair<string, string> key_pair = wrapper.generateRSAKeyPair();
    string str_public_key = key_pair.first;
    string str_private_key = key_pair.second;

    // Original messages
    string sample_msg_1 {"Hello world! This is the first sample message."};
    string sample_msg_2 {"Hello world! This is the second sample message."};
    ASSERT_NE(sample_msg_1, sample_msg_2);

    // Consecutive reencryption
    string consecutive_encr_1 = wrapper.encryptRSAMessage(sample_msg_1, str_public_key);
    string consecutive_decr_1 = wrapper.decryptRSAMessage(consecutive_encr_1, str_private_key);
    EXPECT_EQ(sample_msg_1, consecutive_decr_1);
    
    string consecutive_encr_2 = wrapper.encryptRSAMessage(sample_msg_2, str_public_key);
    string consecutive_decr_2 = wrapper.decryptRSAMessage(consecutive_encr_2, str_private_key);
    EXPECT_EQ(sample_msg_2, consecutive_decr_2);

    // Overlapping reencryption
    string overlapping_encr_1 = wrapper.encryptRSAMessage(sample_msg_1, str_public_key);
    string overlapping_encr_2 = wrapper.encryptRSAMessage(sample_msg_2, str_public_key);

    string overlapping_decr_1 = wrapper.decryptRSAMessage(overlapping_encr_1, str_private_key);
    string overlapping_decr_2 = wrapper.decryptRSAMessage(overlapping_encr_2, str_private_key);

    EXPECT_EQ(sample_msg_1, overlapping_decr_1);
    EXPECT_EQ(sample_msg_2, overlapping_decr_2);

    // Enclosed reencryption
    string enclosed_encr_1 = wrapper.encryptRSAMessage(sample_msg_1, str_public_key);
    string enclosed_encr_2 = wrapper.encryptRSAMessage(sample_msg_2, str_public_key);
    string enclosed_decr_2 = wrapper.decryptRSAMessage(enclosed_encr_2, str_private_key);
    string enclosed_decr_1 = wrapper.decryptRSAMessage(enclosed_encr_1, str_private_key);

    EXPECT_EQ(sample_msg_1, enclosed_decr_1);
    EXPECT_EQ(sample_msg_2, enclosed_decr_2);
}

/**
 * ValidatePublicKeys - Checks that the validatePublicKey() method correctly
 *                      detects valid public keys.
 */
TEST(TestCryptoWrapper_CryptoPP, ValidatePublicKeys){
    CryptoWrapper_Cryptopp wrapper;

    // Test a valid and invalid key
    string valid_public_key = readFile("the-keep/tests/sample_test_keys/KeepPublicKey.test_dat");
    ASSERT_TRUE(wrapper.validatePublicKey(valid_public_key));
    ASSERT_FALSE(wrapper.validatePublicKey("SOME INVALID PRIVATE KEY."));
}


/**
 * ValidatePrivateKeys - Checks that the validatePrivateKey() method correctly
 *                       detects valid private keys.
 */
TEST(TestCryptoWrapper_CryptoPP, ValidatePrivateKeys){
    CryptoWrapper_Cryptopp wrapper;

    // Test a valid and invalid key
    string valid_private_key = readFile("the-keep/tests/sample_test_keys/KeepPrivateKey.test_dat");
    ASSERT_TRUE(wrapper.validatePrivateKey(valid_private_key));
    ASSERT_FALSE(wrapper.validatePrivateKey("SOME INVALID PRIVATE KEY."));
}
