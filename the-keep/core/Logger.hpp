#include <memory>    // for shared_ptr
#include <iostream>  // for cout/cerr
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging

#define DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#define LOG(...) SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)

namespace thekeep 
{

class KeepLogger
{ // coded configuration due to lazyness
   static std::shared_ptr<spdlog::logger> console;       // The default logger: stdout, multi-threaded, colored
   static std::shared_ptr<spdlog::logger> thekeeplogger;
   static std::shared_ptr<spdlog::logger> err_logger;    // Do we need a separate one??

public:
   /// Initialize the logger with an optional log file parameter
   inline static void initialize(const std::string& logfile="logs/thekeeplog.txt") // C++ 17 - static inline supported in a header declaration
   {
      if (!console) try 
      {
         console = spdlog::stdout_color_mt("console");                     // this is actually a default logger; it's already registered
         thekeeplogger = spdlog::basic_logger_mt("basic_logger", logfile); // Create basic (not rotated) file logger
         err_logger = spdlog::stderr_color_mt("stderr"); // Do we need a separate one??
         spdlog::register_logger(thekeeplogger);
         spdlog::register_logger(err_logger);
         spdlog::set_default_logger(console); // TODO: make it configurable/switcheable

         spdlog::info("The default TheKeepId logger {} has been initialized",  spdlog::default_logger_raw()->name());
         // spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
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
};

} // namespace thekeep