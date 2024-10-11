#ifndef CONSOLE_APPENDER_HPP
#define CONSOLE_APPENDER_HPP

#include "appender.hpp"

namespace cmx::Log {

    class ConsoleAppender : public Appender {
    public:
        void append(const std::string& formattedMessage) override;
    };

} // namespace cmx::Log

#endif // CONSOLE_APPENDER_HPP
