#ifndef ASYNC_LOGGER_HPP
#define ASYNC_LOGGER_HPP

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "logger.hpp"

namespace cmx::Log {

    class AsyncLogger : public Logger {
    public:
        explicit AsyncLogger(const std::string& name, LogLevel level = LogLevel::Info);

    private:
        std::queue<std::pair<LogLevel, std::string>> m_messageQueue;
        std::mutex m_mutex;
        std::condition_variable m_condition;
        std::thread m_workerThread;
        bool m_stopWorker = false;

        void workerThread();
    };

} // namespace cmx::Log

#endif // ASYNC_LOGGER_HPP
