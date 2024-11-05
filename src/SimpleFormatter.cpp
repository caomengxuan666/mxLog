//
// Created by CaoMengxuan on 2024/11/5.
//

#include "SimpleFormatter.hpp"
namespace cmx::Log {
    std::string SimpleFormatter::format(const std::string &message, cmx::Log::LogLevel level) const {
        const char* color = LogLevelImpl::toColor(level);
        const char* resetColor = colors::Reset;
        std::string logLevelStr = LogLevelImpl::toString(level);

        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s[%s]%s %s%s%s",
                 color, logLevelStr.c_str(), resetColor, color, message.c_str(), resetColor);

        return std::string(buffer);
    }

}// namespace cmx::Log