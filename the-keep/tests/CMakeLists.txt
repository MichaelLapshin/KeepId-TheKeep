cmake_minimum_required(VERSION 3.18.4)

# Add Tests
add_library(KeepUnitTests OBJECT 
    Test_CryptoWrapper_Cryptopp.cpp
    Test_KeyManager.cpp
)

message("Added UniTest library.")
