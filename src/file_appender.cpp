#include "file_appender.hpp"
#include <stdexcept>
#include <regex>

namespace cmx::Log {

    // 构造函数
    FileAppender::FileAppender(const std::string& filename)
        : m_fileStream(filename, std::ios_base::out | std::ios_base::app) {
        if (!m_fileStream.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    // append 方法：去除控制字符并写入文件
    inline void FileAppender::append(const std::string& formattedMessage)noexcept {
        // 去除控制字符
        static size_t currentBufferSize = 0;

        std::string cleanMessage = removeControlChars(formattedMessage);

        // 写入文件
        m_fileStream << cleanMessage << std::endl;
        //如果达到缓冲区大小，刷新缓冲区
        currentBufferSize+=formattedMessage.size();
        if (currentBufferSize>=m_bufferSize)
        {
            m_fileStream.flush();
            currentBufferSize=0;
        }
    }

    // 辅助函数：去除字符串中的控制字符
    inline std::string FileAppender::removeControlChars(const std::string& input)noexcept {
        // 正则表达式匹配控制字符
        std::regex controlChars("\\x1B\\[[0-9;]*m");
        return std::regex_replace(input, controlChars, "");
    }

    void FileAppender::setBufferSize(size_t newSize) {
        m_bufferSize = newSize;
    }
} // namespace cmx::Log
