cmake_minimum_required(VERSION 3.27)
project(mxLog)

set(CMAKE_CXX_STANDARD 17)


add_executable(mxLog src/main.cpp
        include/logger.hpp
        include/formatter.hpp
        include/appender.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/async_logger.hpp
        include/config.hpp
        src/config.cpp
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
)

target_include_directories(mxLog PRIVATE include)