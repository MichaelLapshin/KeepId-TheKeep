/**
 * @filename: HelperFunctions.cpp
 * @description: A set of common helper functions to use.
 * @author: KeepId
 * @date: February 20, 2022
 */

#include <string>
#include <vector>

#include "HelperFunctions.hpp"

using namespace std;

/*
 * findIndexOfStringInVector()
 */
int findIndexOfStringInVector(const vector<string>& list, const string& search) {
    for(int i = 0; i < list.size(); i++){
        if (list[i] == search) return i;
    }
    return -1;
}
