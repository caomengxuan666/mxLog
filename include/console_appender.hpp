#ifndef CONSOLE_APPENDER_HPP
#define CONSOLE_APPENDER_HPP

#include "appender.hpp"
#include <string>
#include <string_view>
#include <vector>

namespace cmx::Log {

    class ConsoleAppender : public Appender {
    public:
        ConsoleAppender(size_t bufferSize=1024); // 默认缓存区大小为 1024
        inline void append(const std::string &formattedMessage) noexcept override;
        ~ConsoleAppender(); // 确保析构时清空缓冲区

        // 设置输出缓冲区大小
        void setBufferSize(size_t newSize) override;
        void freeRestOfBuffer();

    private:
        std::vector<std::string> messageStorage; // 存储实际的字符串数据
        std::vector<std::string_view> messageBuffer; // 缓存区
        size_t bufferSize; // 缓存区大小

        void flushBuffer(); // 批量输出
    };

} // namespace cmx::Log

#endif // CONSOLE_APPENDER_HPP
