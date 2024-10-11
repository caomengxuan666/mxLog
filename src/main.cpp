#include "file_appender.hpp"
#include "console_appender.hpp"
#include "formatter.hpp"
#include "LogLevel.hpp"
#include <iostream>

int main() {
    // 创建 Formatter
    auto formatter = std::make_unique<cmx::Log::SimpleFormatter>();

    // 创建 FileAppender
    auto fileAppender = std::make_unique<cmx::Log::FileAppender>("log.txt");
    fileAppender->setFormatter(std::move(formatter));

    std::string message = "It's Cmx's LOG SYSTEM!";
    std::string formattedMessage = fileAppender->formatMessage(message, cmx::Log::LogLevel::Info);

    fileAppender->append(formattedMessage);

    // 创建 ConsoleAppender
    auto consoleAppender = std::make_unique<cmx::Log::ConsoleAppender>();

    // 获取 FileAppender 的 Formatter 并设置给 ConsoleAppender
    auto fileFormatter = std::move(fileAppender->getFormatter());
    consoleAppender->setFormatter(std::move(fileFormatter));

    consoleAppender->append(formattedMessage);

    // 更多测试案例
    std::string testMessages[] = {
        "This is a message.",
    };

    for (const auto& msg : testMessages) {
        formattedMessage = fileAppender->formatMessage(msg, cmx::Log::LogLevel::Debug);
        fileAppender->append(formattedMessage);

        formattedMessage = consoleAppender->formatMessage(msg, cmx::Log::LogLevel::Debug);
        consoleAppender->append(formattedMessage);

        formattedMessage = fileAppender->formatMessage(msg, cmx::Log::LogLevel::Info);
        fileAppender->append(formattedMessage);

        formattedMessage = consoleAppender->formatMessage(msg, cmx::Log::LogLevel::Info);
        consoleAppender->append(formattedMessage);

        formattedMessage = fileAppender->formatMessage(msg, cmx::Log::LogLevel::Warning);
        fileAppender->append(formattedMessage);

        formattedMessage = consoleAppender->formatMessage(msg, cmx::Log::LogLevel::Warning);
        consoleAppender->append(formattedMessage);

        formattedMessage = fileAppender->formatMessage(msg, cmx::Log::LogLevel::Error);
        fileAppender->append(formattedMessage);

        formattedMessage = consoleAppender->formatMessage(msg, cmx::Log::LogLevel::Error);
        consoleAppender->append(formattedMessage);

        formattedMessage = fileAppender->formatMessage(msg, cmx::Log::LogLevel::Fatal);
        fileAppender->append(formattedMessage);

        formattedMessage = consoleAppender->formatMessage(msg, cmx::Log::LogLevel::Fatal);
        consoleAppender->append(formattedMessage);
    }

    return 0;
}
