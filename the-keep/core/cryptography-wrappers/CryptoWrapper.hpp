#ifndef CRYPTO_WRAPPER
#define CRYPTO_WRAPPER

#include <string>
#include <utility>

using namespace std;

class CryptoWrapper {
    public:
        virtual pair<string, string> generateRSAKeyPair() const = 0;
        virtual string encryptRSAMessage(string message,
                                         string str_publ_key) const = 0;
        virtual string decryptRSAMessage(string message,
                                         string str_priv_key) const = 0;
    protected:
        const int kNumKeyBitSize = 2048;
    private:
};

#endif