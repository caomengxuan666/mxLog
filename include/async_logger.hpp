#ifndef ASYNC_LOGGER_HPP
#define ASYNC_LOGGER_HPP

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <string>
#include "LogLevel.hpp"
#include "appender.hpp"

namespace cmx::Log {

    class AsyncLogger {
    public:
        explicit AsyncLogger(const std::string& name, LogLevel level = LogLevel::Info);
        ~AsyncLogger();

        // 异步日志接口
        void log(LogLevel level, const std::string& message);

        // 添加控制台和文件日志
        void setFileAppender(const std::string& filePath);
        void setConsoleAppender();

        // 新增接口
        void setLogLevel(LogLevel level);          // 设置日志级别
        void setOutBufferSize(size_t size);        // 设置输出缓冲区大小
        void setBufferSize(size_t size);           // 设置通用缓冲区大小

    private:
        void workerThread();
        void formatAndAppend(const std::string& message, LogLevel level);

        std::string m_name;
        LogLevel m_level;
        std::shared_ptr<Appender> m_fileAppender;
        std::shared_ptr<Appender> m_consoleAppender;

        std::queue<std::pair<LogLevel, std::string>> m_messageQueue;
        std::mutex m_mutex;
        std::condition_variable m_condition;
        std::thread m_workerThread;
        bool m_stopWorker = false;

        // 新增成员变量
        size_t m_outBufferSize = 1024;             // 默认输出缓冲区大小
        size_t m_bufferSize = 1024;                // 默认通用缓冲区大小
    };

} // namespace cmx::Log

#endif // ASYNC_LOGGER_HPP
