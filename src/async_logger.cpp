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
    }

    void AsyncLogger::setBufferSize(size_t size) {
        m_bufferSize = size;
    }

    void AsyncLogger::log(LogLevel level, const std::string &message) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (level >= m_level) {// 仅记录等于或高于当前级别的日志
            m_messageQueue.emplace(level, message);
            m_condition.notify_one();
        }
    }


    void AsyncLogger::setFileAppender(const std::string &filePath) {
        m_fileAppender = std::make_shared<FileAppender>(filePath);
        m_fileAppender->setFormatter(std::make_unique<SimpleFormatter>());
    }

    void AsyncLogger::setConsoleAppender() {
        m_consoleAppender = std::make_shared<ConsoleAppender>();
        m_consoleAppender->setFormatter(std::make_unique<SimpleFormatter>());
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
        std::string formattedMessage = "[" + m_name + "] " + message;

        if (m_fileAppender) {
            m_fileAppender->append(formattedMessage);
        }
        if (m_consoleAppender) {
            m_consoleAppender->append(formattedMessage);
        }
    }

}// namespace cmx::Log
