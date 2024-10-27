#pragma once

#include "LogLevel.hpp"
#include "console_appender.hpp"
#include "file_appender.hpp"
#include "formatter.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace cmx::Log {

    class LogManager {
    private:
        LogLevel currentLevel;

    public:
        // 获取单例实例
        static LogManager &getInstance() {
            static LogManager instance;// 静态实例，保证全局唯一
            return instance;
        }

        // 禁止拷贝构造和赋值操作符
        LogManager(const LogManager &) = delete;
        LogManager &operator=(const LogManager &) = delete;

        // 设置文件日志记录器
        void setFileAppender(const std::string &filePath) {
            fileAppender = std::make_unique<FileAppender>(filePath);
            fileAppender->setFormatter(std::make_unique<SimpleFormatter>());
        }

        // 设置控制台日志记录器
        void setConsoleAppender() {
            consoleAppender = std::make_unique<ConsoleAppender>();
            consoleAppender->setFormatter(std::make_unique<SimpleFormatter>());
        }

        void setCurrentLevel(LogLevel level) {
            currentLevel = level;
        }

        void log(const std::string &message) {
            log(message, currentLevel);
        }

        // 日志输出
        void log(const std::string &message, LogLevel level) {
            if (fileAppender) {
                std::string formattedMessage = formatMessage(message, level);
                fileAppender->append(formattedMessage);
            }

            if (consoleAppender) {
                std::string formattedMessage = formatMessage(message, level);
                consoleAppender->append(formattedMessage);
            }
        }

        void setBufferSize(size_t msg_buffer) {

        }

    private:
        // 私有构造函数，确保外部无法直接实例化
        LogManager() = default;

        // 格式化消息
        std::string formatMessage(const std::string &message, LogLevel level) {


            const char *color = LogLevelImpl::toColor(level);
            const char *resetColor = colors::Reset;
            std::string logLevelStr = LogLevelImpl::toString(level);

            char buffer[1024];
            snprintf(buffer, sizeof(buffer), "%s[%s]%s %s%s%s",
                     color, logLevelStr.c_str(), resetColor, color, message.c_str(), resetColor);

            return std::string(buffer);
        }


        std::unique_ptr<FileAppender> fileAppender;
        std::unique_ptr<ConsoleAppender> consoleAppender;
    };

}// namespace cmx::Log
// namespace cmx::Log


namespace cmx {
    using namespace cmx::Log;
    // 在这里初始化全局唯一的 LogManager 实例
    static cmx::Log::LogManager &logManager = cmx::Log::LogManager::getInstance();
}// namespace cmx

using namespace cmx;