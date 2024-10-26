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
    void FileAppender::append(const std::string& formattedMessage) {
        // 去除控制字符
        std::string cleanMessage = removeControlChars(formattedMessage);

        // 写入文件
        m_fileStream << cleanMessage << std::endl;
        m_fileStream.flush();
    }

    // 辅助函数：去除字符串中的控制字符
    std::string FileAppender::removeControlChars(const std::string& input) {
        // 正则表达式匹配控制字符
        std::regex controlChars("\\x1B\\[[0-9;]*m");
        return std::regex_replace(input, controlChars, "");
    }

} // namespace cmx::Log
