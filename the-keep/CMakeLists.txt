# ----------------------------------------------------------------------------
#  Root CMake file for the Keep
#
#    From the off-tree build directory, invoke:
#      $ cmake <PATH_TO_THE_KEEP_ROOT>
#
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.18.4)

project("TheKeep")

### Disable in-source builds to prevent source tree corruption. ###
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()


### Set build properties ###
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


### Indicates which file is the executable ###
message("Building the Keep debug...")
add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}UnitTests tests/test_main.cpp)

### Main subdirectories to include ###
# add_subdirectory(comms)
add_subdirectory(core)
add_subdirectory(tests)


### Find external libaries ###
find_library(JSON_CPP_PATH jsoncpp)
message("Json C++ library found at: ${JSON_CPP_PATH}")

find_library(CRYPTOPP_PATH crypto++)
message("CryptoPP library found at: ${CRYPTOPP_PATH}")

find_library(GOOGLE_TEST_PATH gtest)
message("Google-Test library found at: ${GOOGLE_TEST_PATH}")

### Adds targets ###
target_link_libraries(${PROJECT_NAME}
  jsoncpp
  crypto++
  HelperFunctions
  DataFields
  CryptoWrappers  
  KeyManager
  TaskManager
)

# Adds targets
target_link_libraries(${PROJECT_NAME}UnitTests
  jsoncpp
  crypto++
  HelperFunctions
  DataFields
  CryptoWrappers  
  KeyManager
  TaskManager
  gtest
  pthread
  KeepUnitTests
)

enable_testing()
