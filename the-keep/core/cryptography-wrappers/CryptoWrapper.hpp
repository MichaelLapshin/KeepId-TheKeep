#ifndef CRYPTO_WRAPPER
#define CRYPTO_WRAPPER

#include <string>
#include <utility>

using namespace std;

class CryptoWrapper {
    public:
        virtual pair<string, string> generateRSAKeyPair() const = 0;
        virtual string encryptRSAMessage(string str_publ_key, 
                                         string message) const = 0;
        virtual string decryptRSAMessage(string str_priv_key, 
                                         string message) const = 0;
    protected:
        const int kNumKeyBitSize = 2048;
    private:
};

#endif