/**
 * @filename: test_common.cpp
 * @description: Definition of the common functions used within the unit tests.
 * @author: KeepId
 * @date: March 15, 2022
 */

#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "assert.h"

#include <jsoncpp/json/json.h>

using namespace std;

/**
 * readFile()
 */
string readFile(string file_path){
    ifstream source_stream (file_path);
    string source_contents;
    source_contents.assign(istreambuf_iterator<char>(source_stream),
                           istreambuf_iterator<char>());
    source_stream.close();
    return source_contents;
}

/**
 * copyFile()
 */
void copyFile(string src_file_path, string dst_file_path){
    string source_contents = readFile(src_file_path);

    // Writes the keys into standard location
    ofstream destination_stream (dst_file_path);
    destination_stream << source_contents;
    destination_stream.close();
}

/**
 * extractJsonValue()
 */
Json::Value extractJsonValue(string file_path){
    try{
        // Reads and returns a Json::Value based on the file contents
        ifstream file_input_stream(file_path);
        Json::Value extracted_json;
        Json::CharReaderBuilder json_builder;
        string err_msg;
        bool parse_success = Json::parseFromStream(json_builder, file_input_stream, &extracted_json, &err_msg);
        return extracted_json;
    }catch(...){
        // Kills the test if the file contents cannot be read
        assert(false);
        return Json::Value();
    }
}

/**
 * vectorsEquivalentContent()
 */
bool vectorsEquivalentContent(vector<string> v1, vector<string> v2){
    bool is_equal = (v1.size() == v2.size());
    for (string e1 : v1){
        
        // Checks that an element from v1 exists in v2
        bool exists = false;
        for (string e2 : v2){
            if (e1 == e2){
                exists = true;
                break;
            }
        }

        // Considers the exists value in the equality of the two vectors
        is_equal &= exists;
    }
    return is_equal;
}
