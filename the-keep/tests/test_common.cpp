/**
 * @filename: test_common.cpp
 * @description: Definition of the common functions used within the unit tests.
 * @author: KeepId
 * @date: March 15, 2022
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

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
