cmake_minimum_required(VERSION 3.27)
project(mxLog)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加动态库
add_library(mxLogLib SHARED
        src/config.cpp
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
        include/logger.hpp
        include/formatter.hpp
        include/appender.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/async_logger.hpp
        include/config.hpp
        include/LogManager.hpp
)

# 设置动态库的输出名称和路径
set_target_properties(mxLogLib PROPERTIES
        OUTPUT_NAME "mxLogLib"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
)

# Windows specific settings
if (WIN32)
    set_target_properties(mxLogLib PROPERTIES
            IMPORT_LIBRARY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/mxLogLib.lib"
    )
endif()

# 添加静态库
add_library(mxLogLibStatic STATIC
        src/config.cpp
        src/console_appender.cpp
        src/file_appender.cpp
        src/formatter.cpp
        include/logger.hpp
        include/formatter.hpp
        include/appender.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/async_logger.hpp
        include/config.hpp
        include/LogManager.hpp
)

# 设置静态库的输出名称和路径
set_target_properties(mxLogLibStatic PROPERTIES
        OUTPUT_NAME "mxLogLibStatic"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
)

# 添加可执行程序，并链接动态库
add_executable(mxLogExample example/main.cpp)
target_include_directories(mxLogExample PRIVATE include)
target_link_libraries(mxLogExample mxLogLib)

# 设置可执行程序的输出路径
set_target_properties(mxLogExample PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
