/**
 * @filename: CryptoWrapper_Cryptopp.cpp
 * @description: Class definition for implementing the main cryptography functions using Crypto++
 * @author: KeepId
 * @date: February 5, 2022
 */

#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/base64.h>
#include <crypto++/files.h>

#include "CryptoWrapper_Cryptopp.hpp"

using namespace std;
using namespace CryptoPP;

/**
 * CryptoWrapper_Cryptopp::generateRSAKeyPair()
 */
pair<string, string> CryptoWrapper_Cryptopp::generateRSAKeyPair() const {
    // Create random generator
    AutoSeededRandomPool random_gen;

    // Creates public/private keys
    RSA::PrivateKey private_key;
    private_key.GenerateRandomWithKeySize(random_gen, ENCRYPTION_KEY_BIT_SIZE);
    RSA::PublicKey public_key(private_key);

    // Validates the keys to the maximum level
    if (!public_key.Validate(random_gen, 3) || !private_key.Validate(random_gen, 3)){
        throw runtime_error("The public or private key generated by crypto++ could not be validated.");
    }

    // Transforms the object keys into strings
    string str_publ_key, str_priv_key;
    public_key.DEREncode(StringSink(str_publ_key).Ref());
    private_key.DEREncode(StringSink(str_priv_key).Ref());

    return pair<string, string>(str_publ_key, str_priv_key);
}

/**
 * CryptoWrapper_Cryptopp::encryptRSAMessage()
 */
string CryptoWrapper_Cryptopp::encryptRSAMessage(string message, string str_publ_key) const {
    // Obtains library-compatible public key object
    RSA::PublicKey public_key;
    StringSource ss_publ_key(str_publ_key, true);
    public_key.BERDecode(ss_publ_key);

    // Create random generator
    AutoSeededRandomPool random_gen;

    // Creates decryptor
    RSAES_OAEP_SHA_Encryptor encryptor(public_key);
    
    // Decrypts the message
    string encrypted_message;
    StringSource string_source( message, true /*pump all*/,
        // The following two 'new' objects will be destroyed automatically by Crypto++
        new PK_EncryptorFilter(random_gen, encryptor, new StringSink(encrypted_message))
    );

    return encrypted_message;
}


/**
 * CryptoWrapper_Cryptopp::decryptRSAMessage()
 */
string CryptoWrapper_Cryptopp::decryptRSAMessage(string message, string str_priv_key) const {
    // Obtains library-compatible private key object
    RSA::PrivateKey private_key;
    StringSource ss_priv_key(str_priv_key, true);
    private_key.BERDecode(ss_priv_key);

    // Create random generator
    AutoSeededRandomPool random_gen;

    // Creates decryptor
    RSAES_OAEP_SHA_Decryptor decryptor(private_key);

    // Decrypts the message
    string decrypted_string;
    StringSource string_source( message, true /*pump all*/,
        // The following two 'new' objects will be destroyed automatically by Crypto++
        new PK_DecryptorFilter(random_gen, decryptor, new StringSink(decrypted_string))
    );

    return decrypted_string;
}

/**
 * CryptoWrapper_Cryptopp::validatePublicKey()
 */
bool CryptoWrapper_Cryptopp::validatePublicKey(string public_key) const {
    // Obtains library-compatible public key object
    RSA::PublicKey rsa_public_key;
    StringSource ss_publ_key(public_key, true);
        
    try{
        rsa_public_key.BERDecode(ss_publ_key);
    } catch(...){
        return false;
    }

    // Create random generator
    AutoSeededRandomPool random_gen;

    return rsa_public_key.Validate(random_gen, 3);
}

/**
 * CryptoWrapper_Cryptopp::validatePrivateKey()
 */
bool CryptoWrapper_Cryptopp::validatePrivateKey(string private_key) const {
    // Obtains library-compatible public key object
    RSA::PrivateKey rsa_private_key;
    StringSource ss_priv_key(private_key, true);
    
    try{
        rsa_private_key.BERDecode(ss_priv_key);
    } catch(...){
        return false;
    }

    // Create random generator
    AutoSeededRandomPool random_gen;

    return rsa_private_key.Validate(random_gen, 3);
}


