/**
 * @filename: test_common.hpp
 * @description: Declaration of the common functions used within the unit tests.
 * @author: KeepId
 * @date: March 15, 2022
 */

#include <string>

#include <jsoncpp/json/json.h>

using namespace std;

const string SAMLE_DATA_FIELDS = "the-keep/tests/sample_data_fields/";

/**
 * readFile()
 * @brief Reads the contents of the given file.
 * 
 * @param[in] file_path The path to the file.
 * 
 * @return The string contents of the file.
 */
string readFile(string file_path);

/**
 * copyFile()
 * @brief Copies the file contents from one location to another.
 * 
 * @param[in] src_file_path The path to the source file.
 * @param[in] dst_file_path The path to the file where to copy to.
 */
void copyFile(string src_file_path, string dst_file_path);

/**
 * extractJsonValue()
 * @brief Reads and records the json structure found within the file
 *        into a Json::Value object.
 * 
 * @param[in] file_path The file to read from.
 * 
 * @return The json value representing the json structure within the file.
 */
Json::Value extractJsonValue(string file_path);

/**
 * vectorsEquivalentContent()
 * @brief Compares the content of two vectors in an unordered fashion.
 * 
 * @param[in] v1 The first vector of strings.
 * @param[in] v2 The second vector of strings.
 * 
 * @return True is both vectors contain the same string elements, otherwise false.
 */
bool vectorsEquivalentContent(vector<string> v1, vector<string> v2);
