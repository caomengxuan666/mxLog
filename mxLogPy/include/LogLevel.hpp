#ifndef MXLOG_LOGLEVEL_HPP
#define MXLOG_LOGLEVEL_HPP

#include <stdexcept>
#include <string>

namespace cmx::Log {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        LogSystem
    };

    inline namespace colors {
        constexpr const char *Reset = "\033[0m";
        constexpr const char *Debug = "\033[0;37m";
        constexpr const char *Info = "\033[0;32m";
        constexpr const char *Warning = "\033[0;33m";
        constexpr const char *Error = "\033[0;31m";
        constexpr const char *Fatal = "\033[0;35m";
        constexpr const char *LogSystem = "\033[1;36m";
    }// namespace colors

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
                case LogLevel::LogSystem:
                    return "LogSystem";
                default:
                    throw std::invalid_argument("Invalid LogLevel");
            }
        }

        static const char *toColor(LogLevel level) {
            switch (level) {
                case LogLevel::Debug:
                    return colors::Debug;
                case LogLevel::Info:
                    return colors::Info;
                case LogLevel::Warning:
                    return colors::Warning;
                case LogLevel::Error:
                    return colors::Error;
                case LogLevel::Fatal:
                    return colors::Fatal;
                case LogLevel::LogSystem:
                    return colors::LogSystem;
                default:
                    return colors::Debug;// 默认颜色
            }
        }
    }// namespace LogLevelImpl


}// namespace cmx::Log

#endif// MXLOG_LOGLEVEL_HPP
