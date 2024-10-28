#include "console_appender.hpp"
#include <iostream>

namespace cmx::Log {

    ConsoleAppender::ConsoleAppender(size_t bufferSize)
        : bufferSize(bufferSize) {}

    void ConsoleAppender::append(const std::string& formattedMessage) {
        // 添加消息到缓存区
        messageBuffer.push_back(formattedMessage);

        // 当缓存区达到指定大小时批量输出
        if (messageBuffer.size() >= bufferSize) {
            flushBuffer();
        }
    }

    void ConsoleAppender::flushBuffer() {
        for (const auto& message : messageBuffer) {
            printf("%s\n", message.c_str());
        }
        messageBuffer.clear();           // 清空缓存区
        //刷新缓冲区
        std::cout.flush();
    }

    ConsoleAppender::~ConsoleAppender() {
        // 确保析构时输出所有剩余消息
        if (!messageBuffer.empty()) {
            flushBuffer();
        }
    }

    void ConsoleAppender::setupOutBufferSize(size_t newSize) {
        bufferSize = newSize;
    }

} // namespace cmx::Log
