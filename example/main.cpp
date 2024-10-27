#include <LogLevel.hpp>
#include <LogManager.hpp>
#include <chrono>
#include <thread>
void benchmarkTest(){
    cmx::logManager.log("BenchMarkTest");
    cmx::logManager.setFileAppender("BenchMarkTest.txt");
    cmx::logManager.setConsoleAppender();

    constexpr size_t test_epoch = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    cmx::logManager.log("Benchmark test");
    cmx::logManager.setBufferSize(test_epoch/100);
    cmx::logManager.setOutBufferSize(test_epoch/100);

    cmx::logManager.setCurrentLevel(LogLevel::Info);
    for (int i = 0; i < test_epoch; i++) {
        cmx::logManager.log("Benchmark test");
    }

    cmx::logManager.log("End of Benchmark test");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    auto time1=std::to_string(duration);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < test_epoch; i++){
        std::cout << "Benchmark test" << i << "\n";
        if(i % 1000 == 0){
            std::cout.flush();
        }
    }
    std::cout<<std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    cmx::logManager.log("std::cout test took " + std::to_string(duration) + " milliseconds"+"with"+std::to_string(test_epoch)+" logs");
    cmx::logManager.log("Benchmark test took " + time1 + " milliseconds"+"with"+std::to_string(test_epoch)+" logs");

}

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
    cmx::logManager.setCurrentLevel(LogLevel::LogSystem);
    cmx::logManager.log("End of Autotest\t\t\n ************************************************");
    manualTest();
    cmx::logManager.log("End of Manual test\t\t\n ************************************************");
    benchmarkTest();

}
