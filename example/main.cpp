#include <LogLevel.hpp>
#include <LogManager.hpp>
#include <chrono>
#include <iostream>
#include <thread>


void benchmarkTest() {
    cmx::logger.log("LogManager Init");
    cmx::logger.log("BenchMarkTest Start", LogLevel::Info);
    cmx::logger.setFileAppender("BenchMarkTest.txt");
    cmx::logger.setConsoleAppender();
    cmx::logger.setLoggerName("cmxLogger");

    //百万级别
    constexpr size_t test_epoch = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    cmx::logger.log("Benchmark test");
    cmx::logger.setBufferSize(test_epoch / 10);
    cmx::logger.setOutBufferSize(test_epoch / 10);

    cmx::logger.setCurrentLevel(LogLevel::Info);
    for (int i = 0; i < test_epoch; i++) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));
        std::string timestamp = buffer;
        cmx::logger.log(timestamp + " - Benchmark test " + std::to_string(i));
        if (i == test_epoch - 1) {
            cmx::logger.log("End of Benchmark test");
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    auto time1 = std::to_string(duration);

    auto start2 = std::chrono::high_resolution_clock::now();
    //然后进行cout的一轮测试
    for (int i = 0; i < test_epoch; i++) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));
        std::string timestamp = buffer;
        std::cout << timestamp + " - Benchmark test " + std::to_string(i) << "\n";
        if (i % 1000 == 0) {
            std::cout.flush();
        }
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2).count();
    auto time2 = std::to_string(duration2);

    cmx::logger.log("Benchmark test took " + time1 + " milliseconds with " + std::to_string(test_epoch) + " logs");
    cmx::logger.log("cout test took " + time2 + " milliseconds with " + std::to_string(test_epoch) + " logs");
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

    for (const auto &msg: testMessages) {
        cmx::logger.log(msg, LogLevel::Debug);
        cmx::logger.log(msg, LogLevel::Info);
        cmx::logger.log(msg, LogLevel::Warning);
        cmx::logger.log(msg, LogLevel::Error);
        cmx::logger.log(msg, LogLevel::Fatal);
    }
}

int main() {
    autoTest();
    cmx::logger.setOutBufferSize(1024);
    cmx::logger.setBufferSize(1024);
    cmx::logger.setCurrentLevel(LogLevel::LogSystem);
    cmx::logger.log("End of Autotest\t\t\n ************************************************");
    manualTest();
    cmx::logger.log("End of Manual test\t\t\n ************************************************");
    cmx::logger.clearConsoleBuffer();


    std::cout << "Press Enter to continue...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::endl;
    cmx::logger.clearConsoleBuffer();


    std::cin.get();


    //benchmarkTest();
}
