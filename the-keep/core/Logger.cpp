/**
 * @filename: Logger.hpp
 * @description: The static members for the global Logger class.
 * @author: KeepId, IL
 * @date: February 13, 2022
 */
#include "Logger.hpp"

std::shared_ptr<spdlog::logger> thekeep::KeepLogger::console;
std::shared_ptr<spdlog::logger> thekeep::KeepLogger::thekeeplogger;
std::shared_ptr<spdlog::logger> thekeep::KeepLogger::err_logger;