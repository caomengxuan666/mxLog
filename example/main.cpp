#include <LogLevel.hpp>
#include <LogManager.hpp>

void manualTest() {
    cmx::logManager.setCurrentLevel(LogLevel::Info);
    cmx::logManager.log("manualTest");

    cmx::logManager.setFileAppender("logAuto.txt");
    cmx::logManager.setConsoleAppender();
    cmx::logManager.setCurrentLevel(LogLevel::Debug);
    std::string message = "Debug message";
    cmx::logManager.log(message);
    cmx::logManager.setCurrentLevel(LogLevel::Error);
    cmx::logManager.log("Error message");
    cmx::logManager.setCurrentLevel(LogLevel::Fatal);
    cmx::logManager.log("Fatal message");
    cmx::logManager.setCurrentLevel(LogLevel::Info);
    cmx::logManager.log("Info message");
    cmx::logManager.setCurrentLevel(LogLevel::Warning);
    cmx::logManager.log("Warning message");
}

//手动版本
void autoTest() {
    // 设置文件日志记录器
    cmx::logManager.setFileAppender("log.txt");
    // 设置控制台日志记录器
    cmx::logManager.setConsoleAppender();
    std::string message = "AUTO TEST";
    cmx::logManager.log(message, cmx::Log::LogLevel::Info);

    // 更多测试消息
    std::string testMessages[] = {
            "This is a Debug message",
    };

    for (const auto &msg: testMessages) {
        cmx::logManager.log(msg, cmx::LogLevel::Debug);
        cmx::logManager.log(msg, cmx::LogLevel::Info);
        cmx::logManager.log(msg, cmx::LogLevel::Warning);
        cmx::logManager.log(msg, cmx::LogLevel::Error);
        cmx::logManager.log(msg, cmx::LogLevel::Fatal);
    }
}

int main() {
    autoTest();
    cmx::logManager.setCurrentLevel(LogLevel::Info);
    cmx::logManager.log("End of Autotest\t\t\n ************************************************");
    manualTest();
}
