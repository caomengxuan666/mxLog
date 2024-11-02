#ifndef FILE_APPENDER_HPP
#define FILE_APPENDER_HPP

#include "appender.hpp"
#include <fstream>

namespace cmx::Log {

    class FileAppender : public Appender {
    public:
        explicit FileAppender(const std::string &filename);
        inline void append(const std::string &formattedMessage) noexcept override;
        inline std::string removeControlChars(const std::string &input) noexcept;
        void setBufferSize(size_t newSize) override;

    private:
        std::ofstream m_fileStream;
        size_t m_bufferSize;
    };

}// namespace cmx::Log

#endif// FILE_APPENDER_HPP
