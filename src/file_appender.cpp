// file_appender.cpp

#include "file_appender.hpp"
#include <stdexcept>

namespace cmx::Log {

    FileAppender::FileAppender(const std::string& filename)
        : m_fileStream(filename, std::ios_base::out | std::ios_base::app) {
        if (!m_fileStream.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    void FileAppender::append(const std::string& formattedMessage) {
        m_fileStream << formattedMessage << std::endl;
        m_fileStream.flush();
    }

} // namespace cmx::Log
