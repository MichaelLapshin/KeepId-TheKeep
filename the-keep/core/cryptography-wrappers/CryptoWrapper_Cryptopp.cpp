
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
    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(random_gen, kNumKeyBitSize);

    // Transformas the object keys into strings
    string str_publ_key, str_priv_key;
    params.DEREncodePublicKey(StringSink(str_publ_key).Ref());
    params.DEREncodePrivateKey(StringSink(str_priv_key).Ref());

    return pair<string, string>(str_publ_key, str_priv_key);
}

/**
 * CryptoWrapper_Cryptopp::encryptRSAMessage()
 */
string CryptoWrapper_Cryptopp::encryptRSAMessage(string str_publ_key, string message) const {
    // Obtains library-compatible public key object
    RSA::PublicKey public_key;
    StringSource ss_publ_key(str_publ_key, true);
    public_key.Load(ss_publ_key);

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
string CryptoWrapper_Cryptopp::decryptRSAMessage(string str_priv_key, string message) const {
    // Obtains library-compatible private key object
    RSA::PrivateKey private_key;
    StringSource ss_priv_key(str_priv_key, true);
    private_key.Load(ss_priv_key);

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
