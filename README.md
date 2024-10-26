# MxLog

## 简介

MxLog是一个基于C++的轻量级日志库

实现了多种级别的不同日志输出，支持不同颜色打印，支持异步输出

### 日志等级分为

* Debug
* Info
* Warning
* Error
* Fatal

## 使用方法
~~~cpp
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
~~~

## 构建案例

* 假设你在Libtorch与QT环境下编译，引入mxLog

~~~cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(custom_ops)

# 设置 CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "D:/MyLibs/libtorch-win-shared-with-deps-2.5.0+cu124/libtorch")
find_package(Torch REQUIRED)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)

# 设置 mxLogLib 的路径
set(MXLOGLIB_LIB_PATH "D:/study/libTorchProject/lib")

# 添加可执行文件
add_executable(main src/simpleModel.cpp)

#设置QT6路径D:\QT_6\6.8.0\msvc2022_64
set(QT_DIR "D:/QT_6/6.8.0/msvc2022_64")
find_package(Qt6 COMPONENTS Core Charts REQUIRED)

# 包含 mxLogLib 和 Qt 的头文件路径
target_include_directories(main PRIVATE include)

# 链接 libtorch 库
target_link_libraries(main PRIVATE "${TORCH_LIBRARIES}")

# 链接 mxLogLib 库
target_link_libraries(main PRIVATE ${MXLOGLIB_LIB_PATH}/mxLogLib.lib)

target_link_libraries(main PRIVATE Qt6::Core Qt6::Charts)


# 查找 lib 文件夹下的所有 .dll 文件
file(GLOB_RECURSE DLL_FILES "${CMAKE_PREFIX_PATH}/lib/*.dll")
file(GLOB MXLOGLIB_DLL_FILES "${MXLOGLIB_LIB_PATH}/*.dll")

# 将找到的 .dll 文件复制到构建目录
foreach(DLL_FILE IN LISTS DLL_FILES MXLOGLIB_DLL_FILES)
    get_filename_component(DLL_NAME ${DLL_FILE} NAME)
    add_custom_command(TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE}
            $<TARGET_FILE_DIR:main>
    )
endforeach()

# 手动 install dll 到安装目录
install(TARGETS main DESTINATION bin)
install(FILES ${DLL_FILES} ${MXLOGLIB_DLL_FILES} DESTINATION bin)

~~~

