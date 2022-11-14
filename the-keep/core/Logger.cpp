#include "Logger.hpp"

std::shared_ptr<spdlog::logger> thekeep::KeepLogger::console;
std::shared_ptr<spdlog::logger> thekeep::KeepLogger::thekeeplogger;
std::shared_ptr<spdlog::logger> thekeep::KeepLogger::err_logger;