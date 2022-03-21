/**
 * @filename: CryptoWrapper_Cryptopp.hpp
 * @description: Class declaration for implementing the main cryptography functions using Crypto++
 * @author: KeepId
 * @date: February 5, 2022
 */

#pragma once

#include <utility>
#include <string>

#include "CryptoWrapper.hpp"

using namespace std;

class CryptoWrapper_Cryptopp : public CryptoWrapper {
    public:
        pair<string, string> generateRSAKeyPair() const override;
        string encryptRSAMessage(string message, string str_publ_key) const override;
        string decryptRSAMessage(string message, string str_priv_key) const override;
        bool validatePublicKey(string public_key) const override;
        bool validatePrivateKey(string private_key) const override;
    protected:
    private:
};
