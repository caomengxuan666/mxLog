#pragma once

#include "async_logger.hpp"
#include "LogLevel.hpp"
#include <memory>
#include <string>

namespace cmx::Log {

    class LogManager {
    public:
        // 单例实例获取方法
        static LogManager& getInstance() {
            static LogManager instance;
            return instance;
        }

        // 设置日志级别
        void setCurrentLevel(LogLevel level) {
            logger->setLogLevel(level);
            logger->log(level, "Current log level is set to: " + LogLevelImpl::toString(level));
        }

        // 设置文件日志记录器
        void setFileAppender(const std::string& filePath) {
            logger->setFileAppender(filePath);
        }

        // 设置控制台日志记录器
        void setConsoleAppender() {
            logger->setConsoleAppender();
        }

        // 输出日志
        void log(const std::string& message, LogLevel level = LogLevel::Info) {
            logger->log(level, message);
        }

        // 设置输出缓冲区大小
        void setOutBufferSize(size_t size) {
            logger->setOutBufferSize(size);
        }

        // 设置通用缓冲区大小
        void setBufferSize(size_t size) {
            logger->setBufferSize(size);
        }

        // 新增接口用于清理控制台缓冲区
        void clearConsoleBuffer() {
            logger->clearConsoleBuffer();
        }

        void setLoggerName(const std::string& name){
            logger->setLoggerName(name);
        }

        void hideLoggerName(){
            logger->hideLoggerName();
        }

        void showLoggerName(){
            logger->showLoggerName();
        }


    private:
        // 在构造函数中初始化 `AsyncLogger` 对象
        LogManager() {
            logger = std::make_unique<AsyncLogger>("CmxLogger");
        }

        std::unique_ptr<AsyncLogger> logger;
    };

} // namespace cmx::Log

// 全局唯一的 `LogManager` 实例
namespace cmx {
    using cmx::Log::LogManager;
    static LogManager& logger = LogManager::getInstance();
} // namespace cmx
using cmx::Log::LogLevel;
