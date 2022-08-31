/**
 * @filename: Test_CassandraCow.cpp
 * @description: To test the Cassandra The Holy Cow static class.
 * @author: KeepId
 * @date: May 13, 2022
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include "test_common.hpp"
#include "../comms/CassandraDriver.hpp"

using namespace std;

/**
 * Connect - Test that the Cassandra Driver can connect and disconnect from a test database
 */
TEST(TestCassandraDriver, ConnectDisconnect){
    // Tests the Key Manager's initialization
    // EXPECT_NO_THROW(KeyManager::initialize());
    // EXPECT_THROW(KeyManager::initialize(), runtime_error);
    // EXPECT_THROW(KeyManager::initialize(), runtime_error);

    // // Tests the Key Manager's uninitialization
    // EXPECT_NO_THROW(KeyManager::uninitialize());
    // EXPECT_THROW(KeyManager::uninitialize(), runtime_error);
}
