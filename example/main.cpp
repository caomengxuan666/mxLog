#include <LogLevel.hpp>
#include <LogManager.hpp>
#include <chrono>
#include <thread>
#include <iostream>


void benchmarkTest() {
    cmx::logger.log("LogManager Init");
    cmx::logger.log("BenchMarkTest Start", LogLevel::Info);
    cmx::logger.setFileAppender("BenchMarkTest.txt");
    cmx::logger.setConsoleAppender();

    constexpr size_t test_epoch = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    cmx::logger.log("Benchmark test");
    cmx::logger.setBufferSize(test_epoch / 10);
    cmx::logger.setOutBufferSize(test_epoch / 10);

    cmx::logger.setCurrentLevel(LogLevel::Info);
    for (int i = 0; i < test_epoch; i++) {
        cmx::logger.log("Benchmark test");
    }

    cmx::logger.log("End of Benchmark test");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    auto time1 = std::to_string(duration);


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < test_epoch; i++) {
        std::cout << "Benchmark test" << i << "\n";
        if (i % 100 == 0) {
            std::cout.flush();
        }
    }
    std::cout << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    cmx::logger.log("std::cout test took " + std::to_string(duration) + " milliseconds with " + std::to_string(test_epoch) + " logs");

    cmx::logger.log("Benchmark test took " + time1 + " milliseconds with " + std::to_string(test_epoch) + " logs");
}

void manualTest() {
    cmx::logger.setCurrentLevel(LogLevel::Info);
    cmx::logger.log("manualTest");

    cmx::logger.setFileAppender("logAuto.txt");
    cmx::logger.setConsoleAppender();
    cmx::logger.setCurrentLevel(LogLevel::Debug);
    std::string message = "Debug message";
    cmx::logger.log(message);
    cmx::logger.setCurrentLevel(LogLevel::Error);
    cmx::logger.log("Error message");
    cmx::logger.setCurrentLevel(LogLevel::Fatal);
    cmx::logger.log("Fatal message");
    cmx::logger.setCurrentLevel(LogLevel::Info);
    cmx::logger.log("Info message");
    cmx::logger.setCurrentLevel(LogLevel::Warning);
    cmx::logger.log("Warning message");
}

// 手动版本
void autoTest() {
    // 设置文件日志记录器
    cmx::logger.setFileAppender("log.txt");
    // 设置控制台日志记录器
    cmx::logger.setConsoleAppender();
    std::string message = "AUTO TEST";
    cmx::logger.log(message, LogLevel::Info);

    // 更多测试消息
    std::string testMessages[] = {
        "This is a Debug message",
    };

    for (const auto &msg : testMessages) {
        cmx::logger.log(msg, LogLevel::Debug);
        cmx::logger.log(msg, LogLevel::Info);
        cmx::logger.log(msg, LogLevel::Warning);
        cmx::logger.log(msg, LogLevel::Error);
        cmx::logger.log(msg, LogLevel::Fatal);
    }
}

int main() {
    autoTest();
    cmx::logger.setOutBufferSize(10);
    cmx::logger.setBufferSize(10);
    cmx::logger.setCurrentLevel(LogLevel::LogSystem);
    cmx::logger.log("End of Autotest\t\t\n ************************************************");
    manualTest();
    cmx::logger.log("End of Manual test\t\t\n ************************************************");
    benchmarkTest();
}
