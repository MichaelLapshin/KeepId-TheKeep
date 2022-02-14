/**
 * @file_name: RunTests.cpp
 * @description: File used to manage and run the unit tests for the Keep.
 * @author: KeepId
 * @date: February 13, 2022
 */

#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

using namespace std;

int main(int argc, char **argv) {
  cout << "Running all unit tests for the Keep." << endl;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}