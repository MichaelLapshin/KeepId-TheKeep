/**
 * @filename: test_common.hpp
 * @description: Declaration of the common functions used within the unit tests.
 * @author: KeepId
 * @date: March 15, 2022
 */

#include <string>

using namespace std;

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
