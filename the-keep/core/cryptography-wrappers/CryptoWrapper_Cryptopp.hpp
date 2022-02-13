/**
 * @filename: CryptoWrapper_Cryptopp.hpp
 * @description: Class declaration for implementing the main cryptography functions using Crypto++
 * @author: KeepId
 * @date: February 5, 2022
 */

#include <utility>
#include <string>

#include "CryptoWrapper.hpp"

using namespace std;

class CryptoWrapper_Cryptopp : public CryptoWrapper {
    public:
        pair<string, string> generateRSAKeyPair() const override;
        string encryptRSAMessage(string str_publ_key, string message) const override;
        string decryptRSAMessage(string str_priv_key, string message) const override;
    protected:
    private:
};
