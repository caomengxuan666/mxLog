#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <LogLevel.hpp>

namespace cmx::Log {

    class Formatter {
    public:
        virtual std::string format(const std::string& message, LogLevel level) const = 0;
    };


} // namespace cmx::Log

#endif // FORMATTER_HPP
