# ----------------------------------------------------------------------------
#  Root CMake file for the Keep
#
#    From the off-tree build directory, invoke:
#      $ cmake <PATH_TO_THE_KEEP_ROOT>
#
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.18.4)

project("TheKeep")

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

# Set build properties
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Indicates which file is the executable
add_executable(${PROJECT_NAME} main.cpp) 

# find_package(CryptoPP REQUIRED)

# Main subdirectories to include
add_subdirectory(comms)
add_subdirectory(core)
# add_subdirectory(cryptopp)

# add_library(libcrypto++ STATIC IMPORTED)

# set_target_properties(libcrypto++ PROPERTIES IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libcrypto++.a)

find_library(CRYPTOPP_PATH crypto++)

message("CryptoPP library found at: ${CRYPTOPP_PATH}")

# Add libraries
# find_package(cryptopp CONFIG REQUIRED)
# target_link_libraries(main PRIVATE cryptopp-static)

# add_library(crypto++ cry)

target_link_libraries(${PROJECT_NAME}
  crypto++
  # cryptopp-static
  CryptoWrappers  
  KeyManager
)

# Add and link external libraries
# find_library(Cryptopp PATHS /home/user/include)

# Determines whether to include the test subdirectories
if(DEBUG)
    message("Building debug version of the Keep...")
    add_subdirectory(test)
endif()
 