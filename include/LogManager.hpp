#pragma once

#include "LogLevel.hpp"
#include "console_appender.hpp"
#include "file_appender.hpp"
#include "formatter.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace cmx::Log {

    class LogManager {
    private:
        LogLevel currentLevel;
        std::vector<char> buffer;// 动态缓冲区

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
            log("LogManager initialized", LogLevel::LogSystem);
            log("Current log level is set to: " + LogLevelImpl::toString(currentLevel), LogLevel::LogSystem);
            log("Current Buffer size is :" + std::to_string(buffer.size()), LogLevel::LogSystem);
            log("Current Output Buffer size is :"+std::to_string(outputBufferSize),LogLevel::LogSystem);
        }

        void setCurrentLevel(LogLevel level) {
            currentLevel = level;
            log("Current log level is set to: " + LogLevelImpl::toString(level), LogLevel::LogSystem);
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

        //设置文件写入缓冲区大小
        void setBufferSize(size_t size) {
            buffer.resize(size);// 动态调整缓冲区大小
        }

        void setOutBufferSize(size_t size){
            if(size<64){
                outputBufferSize=64;
                log("Out Buffer size is too small or you have never set up the buffer size,the defalut size is set up to 64", LogLevel::Warning);
                log("Please use LogManager::setOutBufferSize() to set up the buffer size",LogLevel::Warning);
            }
            log("Current Buffer size is set up to :" + std::to_string(outputBufferSize), LogLevel::LogSystem);
            outputBufferSize=size;  //手动设置输出缓冲区大小
            consoleAppender->setupOutBufferSize(outputBufferSize);
        }

    private:
        // 私有构造函数，确保外部无法直接实例化
        LogManager() = default;

        // 格式化消息
        std::string formatMessage(const std::string &message, LogLevel level) {
            const char *color = LogLevelImpl::toColor(level);
            const char *resetColor = colors::Reset;
            std::string logLevelStr = LogLevelImpl::toString(level);

            // 使用动态缓冲区
            if (buffer.size() < 128) {
                buffer.resize(128);// 确保缓冲区足够大
                log("Buffer size is too small or you have never set up the buffer size,the defalut size is set up to 128", LogLevel::Warning);
                log("Please use LogManager::setBufferSize() to set up the buffer size",LogLevel::Warning);
                log("Current Buffer size is :" + std::to_string(buffer.size()), LogLevel::LogSystem);
            }
            snprintf(buffer.data(), buffer.size(), "%s[%s]%s %s%s%s",
                     color, logLevelStr.c_str(), resetColor, color, message.c_str(), resetColor);

            return std::string(buffer.data());
        }

        std::unique_ptr<FileAppender> fileAppender;
        std::unique_ptr<ConsoleAppender> consoleAppender;
        size_t outputBufferSize=128;
    };

}// namespace cmx::Log

namespace cmx {
    using namespace cmx::Log;
    // 在这里初始化全局唯一的 LogManager 实例
    static cmx::Log::LogManager &logManager = cmx::Log::LogManager::getInstance();
}// namespace cmx

using namespace cmx;
