#ifndef MXLOG_LOGLEVEL_HPP
#define MXLOG_LOGLEVEL_HPP

#include <string>
#include <stdexcept>

namespace cmx::Log {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    namespace LogLevelImpl {
        static std::string toString(LogLevel level) {
            switch (level) {
                case LogLevel::Debug:
                    return "Debug";
                case LogLevel::Info:
                    return "Info";
                case LogLevel::Warning:
                    return "Warning";
                case LogLevel::Error:
                    return "Error";
                case LogLevel::Fatal:
                    return "Fatal";
                default:
                    throw std::invalid_argument("Invalid LogLevel");
            }
        }

        static const char* toColor(LogLevel level) {
            switch (level) {
                case LogLevel::Debug:
                    return "\033[0;37m";
                case LogLevel::Info:
                    return "\033[0;32m";
                case LogLevel::Warning:
                    return "\033[0;33m";
                case LogLevel::Error:
                    return "\033[0;31m";
                case LogLevel::Fatal:
                    return "\033[0;35m";
                default:
                    return "\033[0;37m";
            }
        }
    }

    inline namespace colors {
        constexpr const char* Reset = "\033[0m";
        constexpr const char* Debug = "\033[0;37m";
        constexpr const char* Info = "\033[0;32m";
        constexpr const char* Warning = "\033[0;33m";
        constexpr const char* Error = "\033[0;31m";
        constexpr const char* Fatal = "\033[0;35m";
    }

} // namespace cmx::Log

#endif // MXLOG_LOGLEVEL_HPP
