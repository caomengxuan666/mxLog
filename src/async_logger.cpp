#include "async_logger.hpp"
#include "console_appender.hpp"
#include "file_appender.hpp"
#include "formatter.hpp"

namespace cmx::Log {

    AsyncLogger::AsyncLogger(const std::string &name, LogLevel level)
        : m_name(name), m_level(level), m_workerThread(&AsyncLogger::workerThread, this) {
    }

    AsyncLogger::~AsyncLogger() {
        m_stopWorker = true;
        m_condition.notify_all();
        if (m_workerThread.joinable()) {
            m_workerThread.join();
        }
    }

    void AsyncLogger::setLogLevel(LogLevel level) {
        m_level = level;
    }

    void AsyncLogger::setOutBufferSize(size_t size) {
        m_outBufferSize = size;
        log(LogLevel::LogSystem, "The output buffer size has been changed to: " + std::to_string(size));
    }

    void AsyncLogger::setBufferSize(size_t size) {
        m_bufferSize = size;
        log(LogLevel::LogSystem, "The buffer size has been changed to: " + std::to_string(size));
    }

    void AsyncLogger::log(LogLevel level, const std::string &message) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (level >= m_level) { // 仅记录等于或高于当前级别的日志
            m_messageQueue.emplace(level, message);
            m_condition.notify_one();
        }
    }

    void AsyncLogger::setFileAppender(const std::string &filePath) {
        m_fileAppender = std::make_shared<FileAppender>(filePath);
        m_fileAppender->setFormatter(std::make_unique<SimpleFormatter>());
        fileAppenderSet = true;
    }

    void AsyncLogger::setConsoleAppender() {
        m_consoleAppender = std::make_shared<ConsoleAppender>();
        m_consoleAppender->setFormatter(std::make_unique<SimpleFormatter>());
        consoleAppenderSet = true;
    }

    void AsyncLogger::workerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this] { return !m_messageQueue.empty() || m_stopWorker; });

            if (m_stopWorker && m_messageQueue.empty()) break;

            auto [level, message] = m_messageQueue.front();
            m_messageQueue.pop();
            lock.unlock();

            formatAndAppend(message, level);
        }
    }

    void AsyncLogger::formatAndAppend(const std::string &message, LogLevel level) {
        // 获取格式化的日志消息
        std::string formattedMessage = "[" + m_name + "] " + LogLevelImpl::toColor(level) + "["+LogLevelImpl::toString(level) + "] : " + message + colors::Reset;

        // 将日志消息写入到文件和控制台
        if (fileAppenderSet) {
            m_fileAppender->append(formattedMessage);
        }
        if (consoleAppenderSet) {
            m_consoleAppender->append(formattedMessage);
        }
    }

} // namespace cmx::Log
