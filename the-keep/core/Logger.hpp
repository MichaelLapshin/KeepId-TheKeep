/**
 * @filename: Logger.hpp
 * @description: The declaration for the global Logger class.
 * @author: KeepId, IL
 * @date: February 13, 2022
 */
#pragma once
#include <memory>    // for shared_ptr
#include <iostream>  // for cout/cerr
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging

#include "core/data-fields/Constants.hpp"  // for LOG_FILE_NAME, environment(DEV); TODO: may need to be moved

// Convenience macros
#define DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#define LOG(...) SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)

namespace thekeep 
{

/** Main Global Logger class for TheKeep. Uses SpdLog header-only library. */
class KeepLogger
{ // coded configuration due to lazyness
   static std::shared_ptr<spdlog::logger> console;       // The default logger: stdout, multi-threaded, colored
   static std::shared_ptr<spdlog::logger> thekeeplogger; // defaults to "logs/thekeeplog.txt"
   static std::shared_ptr<spdlog::logger> err_logger;    // Do we need a separate one??

public:
   /// Initialize the logger with an optional log file parameter
   inline static void initialize(const std::string& logfile=LOG_FILE_NAME) // C++ 17 - static inline supported in a header declaration
   {
      if (!console) try 
      {
         console = spdlog::stdout_color_mt("console");                      // this is actually a default logger; it's already registered
         thekeeplogger = spdlog::basic_logger_mt("thekeeplogger", logfile); // Create & register basic (not rotated) file logger; not truncate
         err_logger = spdlog::stderr_color_mt("stderr"); // Do we need a separate one??
      // for multiple sinks (console+file) in the future:   spdlog::register_logger(thekeeplogger);

         if(!DEVELOPMENT)
            spdlog::set_default_logger(thekeeplogger);    // TODO: make it configurable/switcheable
         thekeeplogger->flush_on(spdlog::level::err);  // Trigger automatic flash on errors

         spdlog::info("The default TheKeepId logger '{}' has been initialized",  spdlog::default_logger_raw()->name());
      }
      catch (const spdlog::spdlog_ex &ex)
      {
         std::cerr << "Log initialization failed: " << ex.what() << std::endl;
      }
   }

   const inline static spdlog::logger& logger() { return *thekeeplogger; } // getter... hate them
 
   KeepLogger()
   {
      initialize();  // just in case
      spdlog::info("Hello, TheKeepId {}!", "World");
   }

   inline static void flash() {  thekeeplogger->flush(); }
};

} // namespace thekeep