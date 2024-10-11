// console_appender.cpp

#include "console_appender.hpp"
#include <iostream>

namespace cmx::Log {

    void ConsoleAppender::append(const std::string& formattedMessage) {
        std::cout << formattedMessage << std::endl;
    }

} // namespace cmx::Log
