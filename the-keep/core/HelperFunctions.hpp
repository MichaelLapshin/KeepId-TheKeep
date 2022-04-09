/**
 * @filename: HelperFunctions.hpp
 * @description: Declaration of the Keep helper functions.
 * @author: KeepId
 * @date: March 6, 2022
 */

#pragma once

#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

using namespace std;

/**
 * findIndexOfStringInVector()
 * @brief Finds the index of a string within a vector of strings. 
 * 
 * @param[in] list The vector of strings.
 * @param[in] search The string to find in the vector.
 * 
 * @return The index at which the string was found in the vector, or -1 if none was found.
 */
int findIndexOfStringInVector(const vector<string>& list, const string& search);

/**
 * parseJsonString()
 * @brief Parses the json into its Json::Value object.
 * 
 * @param[in] json_str The string representing the Json object.
 * 
 * @throw If the string could not be parsed.
 * @return The Json::Value object parsed from the string.
 */
Json::Value parseJsonString(string json_str);