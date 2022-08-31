cmake_minimum_required(VERSION 3.18.4)

# Add Tests
add_library(KeepUnitTests OBJECT
    test_common.cpp
    Test_CryptoWrapper_Cryptopp.cpp
    Test_DataField_Assertions.cpp
    Test_DataField_Config.cpp
    Test_HelperFunctions.cpp
    Test_KeyManager.cpp
    Test_TaskManager.cpp
    Test_CassandraCow.cpp
)

message("Added UniTest library.")
