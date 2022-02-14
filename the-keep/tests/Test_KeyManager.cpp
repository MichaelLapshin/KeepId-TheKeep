#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

#include "../core/key-manager/KeyManager.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper.hpp"
#include "../core/cryptography-wrappers/CryptoWrapper_Cryptopp.hpp"

using namespace std;

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
    // CryptoWrapper_Cryptopp wrapper;
    // ASSERT_NO_THROW(KeyManager::initialize(&wrapper));

    // 
}

/**
 * Generate 
 */

/**
 * ReadStorageKey - Test that the KeyManager correctly 
 */

/**
 * EncryptDecryptMessageSimple - Test that a string can be encrypted
 *              and decrypted 
 */
TEST(TestKeyManager, EncryptDecryptMessageSimple){

}

/**
 * EncryptDecryptMessageComplex - Test 
 */
TEST(TestKeyManager, EncryptDecryptMessageComplex){

}
