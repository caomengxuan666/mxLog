cmake_minimum_required(VERSION 3.27)
project(mxLog)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 静态库输出路径

# 添加静态库
add_library(mxLogLib STATIC
        src/config.cpp
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
        include/appender.hpp
        include/async_logger.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/formatter.hpp
        include/config.hpp
        include/logger.hpp
        include/LogLevel.hpp
        include/LogManager.hpp
)

# 设置静态库的输出名称和路径
set_target_properties(mxLogLib PROPERTIES
        OUTPUT_NAME "mxLogLib"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}  # 确保生成 .lib 文件
)

#添加动态库
add_library(mxLogLibShared SHARED
        src/config.cpp
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
        include/appender.hpp
        include/async_logger.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/formatter.hpp
        include/config.hpp
        include/logger.hpp
        include/LogLevel.hpp
        include/LogManager.hpp
)
# 设置动态库的输出名称和路径
set_target_properties(mxLogLibShared PROPERTIES
        OUTPUT_NAME "mxLogLibShared"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}  # 确保生成 .dll 文件
)

# 添加可执行程序，并链接静态库
add_executable(mxLogExample example/main.cpp)
target_include_directories(mxLogExample PRIVATE include)
target_link_libraries(mxLogExample PRIVATE mxLogLib)  # 直接链接静态库


# 设置可执行程序的输出路径
set_target_properties(mxLogExample PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
