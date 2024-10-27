#ifndef CONSOLE_APPENDER_HPP
#define CONSOLE_APPENDER_HPP

#include "appender.hpp"
#include <vector>
#include <string>

namespace cmx::Log {

    class ConsoleAppender : public Appender {
    public:
        ConsoleAppender(size_t bufferSize = 128); // 默认缓存区大小为 128
        void append(const std::string& formattedMessage) override;
        ~ConsoleAppender(); // 确保析构时清空缓冲区

        //设置输出缓冲区大小
        void setupOutBufferSize(size_t newSize);

    private:
        std::vector<std::string> messageBuffer; // 缓存区
        size_t bufferSize; // 缓存区大小

        void flushBuffer(); // 批量输出
    };

} // namespace cmx::Log

#endif // CONSOLE_APPENDER_HPP
