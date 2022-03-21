/**
 * @filename: HelperFunctions.hpp
 * @description: Declaration of the Keep helper functions.
 * @author: KeepId
 * @date: March 6, 2022
 */

#ifndef HELPER_FUNCTIONS 
#define HELPER_FUNCTIONS 

#include <string>
#include <vector>

using namespace std;

/*
 * findIndexOfStringInVector()
 * @brief Finds the index of a string within a vector of strings. 
 * 
 * @param[in] list The vector of strings.
 * @param[in] search The string to find in the vector.
 * 
 * @return The index at which the string was found in the vector, or -1 if none was found.
 */
int findIndexOfStringInVector(const vector<string>& list, const string& search);

#endif
