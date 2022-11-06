#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define DEBUG(...) SPDLOG_LOGGER_DEBUG(spdlog::default_logger_raw(), __VA_ARGS__)
#define LOG(...) SPDLOG_LOGGER_INFO(spdlog::default_logger_raw(), __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_WARN(spdlog::default_logger_raw(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(spdlog::default_logger_raw(), __VA_ARGS__)

namespace thekeep {

// coded configuration due to lazyness
class KeepLogger {

    std::shared_ptr<spdlog::logger> console = spdlog::stdout_color_mt("console");    
    std::shared_ptr<spdlog::logger> err_logger = spdlog::stderr_color_mt("stderr");    

   // spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");

    public:
         static std::shared_ptr<spdlog::logger> thekeeplogger; 

         KeepLogger() {
            // initialize the logger with parameters


            //Use the default logger (stdout, multi-threaded, colored)
            spdlog::info("Hello, TheKeepId {}!", "World");
         }
};

} // namespace thekeep