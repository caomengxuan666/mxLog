#include "console_appender.hpp"
#include <iostream>
#include <sstream>

namespace cmx::Log {

    ConsoleAppender::ConsoleAppender(size_t bufferSize)
        : bufferSize(bufferSize){}

    inline void ConsoleAppender::append(const std::string &formattedMessage) noexcept {
        // 将实际的字符串数据存储在 messageStorage 中
        messageStorage.emplace_back(formattedMessage);

        // 使用 string_view 引用 messageStorage 中的字符串
        messageBuffer.emplace_back(messageStorage.back());

        // 当缓存区达到指定大小时批量输出
        if (messageBuffer.size() >= bufferSize) {
            flushBuffer();
            messageBuffer.clear(); // 清空缓存区
            std::cout.flush();     // 刷新缓冲区
        }
    }

    void ConsoleAppender::flushBuffer() {
        std::stringstream ss;
        for (const auto &message : messageBuffer) {
            if (!message.empty()) { // 确保消息不为空
                ss << message << "\n";
            }

        }
        std::cout << ss.str();
    }

    void ConsoleAppender::freeRestOfBuffer() {
        if (!messageBuffer.empty()) {
            flushBuffer();
            messageBuffer.clear();
            std::cout.flush();
        }
    }

    ConsoleAppender::~ConsoleAppender() {
        // 确保析构时输出所有剩余消息
        freeRestOfBuffer();
    }

    void ConsoleAppender::setBufferSize(size_t newSize) {
        bufferSize = newSize;
        freeRestOfBuffer();
        messageBuffer.clear(); // 先清空
        messageBuffer.resize(newSize); // 调整缓存区大小
    }

} // namespace cmx::Log
