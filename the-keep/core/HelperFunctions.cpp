/**
 * @filename: HelperFunctions.cpp
 * @description: A set of common helper functions to use.
 * @author: KeepId
 * @date: February 20, 2022
 */

#include <string>
#include <vector>
#include <unique_ptr>

#include <jsoncpp/json/json.h>

#include "HelperFunctions.hpp"

using namespace std;

/**
 * findIndexOfStringInVector()
 */
int findIndexOfStringInVector(const vector<string>& list, const string& search) {
    for(int i = 0; i < list.size(); i++){
        if (list[i] == search) return i;
    }
    return -1;
}

/**
 * Parse Json string
 */
Json::Value parseJsonString(string json_str){
    // Create JsonCpp objects necessary for parsing the Json string
    Json::Value json_obj;
    Json::CharReaderBuilder builder;
    unique_ptr<Json::CharReader> reader = make_unique(builder.newCharReader()); // TODO: double check if this unique_ptr pointer syntax is correct
    Json::String errors;

    // Parse the string
    bool success = reader->parse(json_str.c_str(),
                                 json_str.c_str() + json_str.size(), 
                                 &json_obj, 
                                 &errors);

    // Handle the result
    if (!success){
        throw runtime_error("A Json string could not be parsed into a Json::Value object. Error: " + errors);
    }
    return json_obj;
}
