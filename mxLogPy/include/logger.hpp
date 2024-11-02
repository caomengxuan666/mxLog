#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <memory>
#include <string>
#include "LogLevel.hpp"
#include "appender.hpp"

namespace cmx::Log {

    class Logger {
    public:
        explicit Logger(const std::string& name, LogLevel level = LogLevel::Info);

        void log(LogLevel level, const std::string& message);

    private:
        std::string m_name;
        LogLevel m_level;
        std::shared_ptr<Appender> m_appender;
    };

} // namespace cmx::Log

#endif // LOGGER_HPP
