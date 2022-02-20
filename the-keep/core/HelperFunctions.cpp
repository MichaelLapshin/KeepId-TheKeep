/**
 * @filename: HelperFunctions.cpp
 * @description: A set of common helper functions to use.
 * @author: KeepId
 * @date: February 20, 2022
 */

#include <string>
#include <vector>

/*
 * getIndexOfString()
 * @brief Finds the index of a string within a vector of strings. 
 * 
 * @param[in] list The vector of strings.
 * @param[in] search The string to find in the vector.
 * 
 * @return The index at which the string was found in the vector, or -1 if none was found.
 */
int findVectorString(const std::vector<std::string>& list, const std::string& search) {
    for(int i = 0; i < list.size(); i++){
        if (list[i] == search) return i;
    }
    return -1;
}