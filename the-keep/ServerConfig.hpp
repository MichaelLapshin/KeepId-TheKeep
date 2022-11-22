/**
 * @filename: ServerConfig.hpp
 * @description: The declaration of the parser for the data field configuration file.
 * @author: KeepId, IL
 * @date: November 18, 2022
 */
#pragma once

#include <string>
#include <vector>
#include <memory>

#include <jsoncpp/json/json.h>

using namespace std;

// TODO: implement required file-based configuration 
class ServerConfig{
    public:

//TODO: convert to a singleton.. add initialization from an actual file
        /**
         * Config::initialize()
         * @brief Intializes the configuration file. Read from the file
         *        specified in 'MAIN_CONFIG_FILE_NAME' of Constants.hpp.
         * @throw The configuration file does not follow the correct format.
         */
        static void initialize();

    
};