# Add KeyManager
add_library(KeyManager
    key-manager/KeyManager.cpp
    key-manager/KeyManager.hpp
)

message("Added KeyManager library.")

# Add CryptoWrappers
add_library(CryptoWrappers 
    cryptography-wrappers/CryptoWrapper_Cryptopp.cpp

    cryptography-wrappers/CryptoWrapper_Cryptopp.hpp
    cryptography-wrappers/CryptoWrapper.hpp
)

# Message
message("Added CryptoWrappers library.")
