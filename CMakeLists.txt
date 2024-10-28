cmake_minimum_required(VERSION 3.27)
project(mxLog)

set(CMAKE_CXX_STANDARD 17)
# 由于我引入string_view，必须要求C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(include)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 动态库输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 静态库输出路径

# 开启 O2 优化
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")

# 添加静态库
add_library(mxLogLib STATIC
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
        include/appender.hpp
        include/async_logger.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/formatter.hpp
        include/logger.hpp
        include/LogLevel.hpp
        include/LogManager.hpp
        src/async_logger.cpp
)

# 设置静态库的输出名称和路径
set_target_properties(mxLogLib PROPERTIES
        OUTPUT_NAME "mxLogLib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"  # 确保生成 .lib 文件
)

# 添加动态库
add_library(mxLogLibShared SHARED
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
        include/appender.hpp
        include/async_logger.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/formatter.hpp
        include/logger.hpp
        include/LogLevel.hpp
        include/LogManager.hpp
        src/async_logger.cpp
)

# 设置动态库的输出名称和路径
set_target_properties(mxLogLibShared PROPERTIES
        OUTPUT_NAME "mxLogLibShared"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"  # 确保生成 .dll 文件
)

# 添加可执行程序，并链接静态库
add_executable(mxLogExample example/main.cpp)
target_include_directories(mxLogExample PRIVATE include)
target_link_libraries(mxLogExample PRIVATE mxLogLib)  # 直接链接静态库

# 设置可执行程序的输出路径
set_target_properties(mxLogExample PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# 设置 Release 和 Debug 构建的自定义输出路径
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/DEBUG")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/DEBUG")
    set_target_properties(mxLogLib PROPERTIES OUTPUT_NAME "mxLogLibd")  # 在 Debug 下带 d
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/Release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/Release")
endif()

#设置pybind路径D:\MyLibs\pybind11
#添加CMAKE_PREFIX_PATH，用于搜索依赖项的头文件和库文件
list(APPEND CMAKE_PREFIX_PATH "D:/MyLibs/pybind11")
# 引入 pybind11 并添加 python_module 子目录
find_package(pybind11 REQUIRED)
add_subdirectory(python_module)


# 安装规则：将生成的 dll 和 lib 文件复制到项目源码目录的 lib 文件夹
install(TARGETS mxLogLib mxLogLibShared mxLogExample
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib
)
