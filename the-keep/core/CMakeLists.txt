# Add HelperFunctions
add_library(HelperFunctions STATIC
    HelperFunctions.cpp
    Logger.cpp
)
message("Added HelperFunctions library.")

# Add KeyManager
add_library(KeyManager STATIC
    key-manager/KeyManager.cpp
    cryptography-wrappers/CryptoWrapper_Cryptopp.cpp
)
message("Added KeyManager library.")

# Add CryptoWrappers
add_library(CryptoWrappers STATIC
    cryptography-wrappers/CryptoWrapper_Cryptopp.cpp
)
message("Added CryptoWrappers library.")

# Add TaskManager
add_library(TaskManager STATIC
    task-manager/TaskManager.cpp
    task-manager/TaskLogic.cpp
)
message("Added TaskManager library.")

# Add DataFields
add_library(DataFields STATIC
    data-fields/Assertions.cpp
    data-fields/Config.cpp
    HelperFunctions.cpp
)
message("Added Assertions library.")
