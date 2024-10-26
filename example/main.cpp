#include <LogManager.hpp>
#include <LogLevel.hpp>

int main() {
    // 设置文件日志记录器
    cmx::logManager.setFileAppender("log.txt");
    // 设置控制台日志记录器
    cmx::logManager.setConsoleAppender();
    std::string message = "It's Cmx's LOG SYSTEM!";
    cmx::logManager.log(message, cmx::Log::LogLevel::Info);

    // 更多测试消息
    std::string testMessages[] = {
            "This is a Debug message",
    };

    for (const auto& msg : testMessages) {
        cmx::logManager.log(msg, cmx::LogLevel::Debug);
        cmx::logManager.log(msg, cmx::LogLevel::Info);
        cmx::logManager.log(msg, cmx::LogLevel::Warning);
        cmx::logManager.log(msg, cmx::LogLevel::Error);
        cmx::logManager.log(msg, cmx::LogLevel::Fatal);
    }

    return 0;
}
