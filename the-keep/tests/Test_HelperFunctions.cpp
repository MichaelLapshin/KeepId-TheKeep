/**
 * @filename: Test_HelperFunctions.cpp
 * @description: To test the helper functions of the Keep.
 * @author: KeepId
 * @date: March 6, 2022
 */

#include "../core/HelperFunctions.hpp"

#include <gtest/gtest.h>

using namespace std;

/**
 * findIndexOfStringInVector_normal - A series of tests checking the normal use
 *                      of the helper functions findIndexOf() function. 
 */
TEST(TestHelperFunctions, findIndexOfStringInVector_normal){
    // Create sample list
    vector<string> sample_list(4);
    sample_list[0] = "abc";
    sample_list[1] = "ab";
    sample_list[2] = "abcd";
    sample_list[3] = "e";

    // Tests non-existance elements for correct output
    EXPECT_EQ(findIndexOfStringInVector(sample_list, ""), -1);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "a"), -1);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "abd"), -1);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "abcde"), -1);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "f"), -1);

    // Tests elements of thelist for the correct output
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "abc"), 0);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "ab"), 1);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "abcd"), 2);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "e"), 3);
}

/**
 * findIndexOfStringInVector_empty - Tests that the findIndexOfStringInVector() helper
 *                                   function works correctly when the given string vector is empty.
 */
TEST(TestHelperFunctions, findIndexOfStringInVector_empty){
    // Create sample list
    vector<string> sample_list;

    // Tests non-existance elements for correct output
    EXPECT_EQ(findIndexOfStringInVector(sample_list, ""), -1);
    EXPECT_EQ(findIndexOfStringInVector(sample_list, "a"), -1);
}
