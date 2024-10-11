#ifndef APPENDER_HPP
#define APPENDER_HPP

#include <string>
#include <memory>
#include <LogLevel.hpp>
#include <formatter.hpp>

namespace cmx::Log {

    class Formatter;

    class Appender {
    protected:
        std::unique_ptr<Formatter> m_formatter;

    public:
        virtual ~Appender() = default;
        virtual void append(const std::string& formattedMessage) = 0;

        void setFormatter(std::unique_ptr<Formatter> formatter) {
            m_formatter = std::move(formatter);
        }

        // 返回可移动的 std::unique_ptr<Formatter>
        std::unique_ptr<Formatter> getFormatter() {
            return std::move(m_formatter);
        }

        std::string formatMessage(const std::string& message, LogLevel level) const {
            if (m_formatter) {
                return m_formatter->format(message, level);
            }
            return message;
        }
    };

} // namespace cmx::Log

#endif // APPENDER_HPP
