# Add KeyManager
add_library(KeyManager STATIC
    key-manager/KeyManager.cpp
    # key-manager/KeyManager.hpp
)
message("Added KeyManager library.")

# Add CryptoWrappers
add_library(CryptoWrappers STATIC
    cryptography-wrappers/CryptoWrapper_Cryptopp.cpp

    # cryptography-wrappers/CryptoWrapper_Cryptopp.hpp
    # cryptography-wrappers/CryptoWrapper.hpp
)
message("Added CryptoWrappers library.")

# Add TaskManager
add_library(TaskManager STATIC
    task-manager/TaskManager.cpp
)
message("Added TaskManager library.")

# Add DataFields
add_library(DataFields STATIC
    data-fields/Constants.hpp
    data-fields/Assertions.cpp
    data-fields/Config.cpp
)
message("Added Assertions library.")

# Add HelperFunctions
add_library(HelperFunctions STATIC
    HelperFunctions.cpp
)
message("Added Assertions library.")
