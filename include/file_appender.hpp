#ifndef FILE_APPENDER_HPP
#define FILE_APPENDER_HPP

#include <fstream>
#include "appender.hpp"

namespace cmx::Log {

    class FileAppender : public Appender {
    public:
        explicit FileAppender(const std::string& filename);
        void append(const std::string& formattedMessage) override;
        std::string removeControlChars(const std::string& input);

    private:
        std::ofstream m_fileStream;
    };

} // namespace cmx::Log

#endif // FILE_APPENDER_HPP
