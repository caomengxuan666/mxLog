cmake_minimum_required(VERSION 3.15)
project(mxLogPy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(PROJECT_FILES
        ../src/console_appender.cpp
        ../src/file_appender.cpp
        ../src/async_logger.cpp
        ../src/SimpleFormatter.cpp
        ../include/appender.hpp
        ../include/async_logger.hpp
        ../include/console_appender.hpp
        ../include/file_appender.hpp
        ../include/formatter.hpp
        ../include/LogLevel.hpp
        ../include/LogManager.hpp
        ../include/SimpleFormatter.hpp
)

include_directories(../include)

set(CMAKE_PREFIX_PATH "D:/MyLibs/pybind11/share/cmake/pybind11")

find_package(pybind11 REQUIRED)

# 定义 Python 模块，不使用动态库
pybind11_add_module(mxLogPy MODULE
        pybind_wrapper.cpp
        ${PROJECT_FILES}
)

