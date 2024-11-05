cmake_minimum_required(VERSION 3.27)
project(mxLog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(include)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 动态库输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 静态库输出路径

# 设置 Release 和 Debug 构建的自定义输出路径
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/DEBUG")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/DEBUG")
    add_definitions(-D_DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
else ()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/Release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/Release")
    add_definitions(-DNDEBUG)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif ()

# 添加静态库
add_library(mxLogLib STATIC
        src/console_appender.cpp
        src/file_appender.cpp
        include/appender.hpp
        include/async_logger.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/formatter.hpp
        include/LogLevel.hpp
        include/LogManager.hpp
        src/async_logger.cpp
        src/SimpleFormatter.cpp
        include/SimpleFormatter.hpp
)

# 设置静态库的输出名称和路径
set_target_properties(mxLogLib PROPERTIES
        OUTPUT_NAME "mxLogLib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(mxLogLib PROPERTIES OUTPUT_NAME "mxLogLibd")
endif ()

# 添加动态库
add_library(mxLogLibShared SHARED
        src/console_appender.cpp
        src/file_appender.cpp
        include/appender.hpp
        include/async_logger.hpp
        include/console_appender.hpp
        include/file_appender.hpp
        include/formatter.hpp
        include/LogLevel.hpp
        include/LogManager.hpp
        src/async_logger.cpp
        src/SimpleFormatter.cpp
        include/SimpleFormatter.hpp
)

# 设置动态库的输出名称和路径
set_target_properties(mxLogLibShared PROPERTIES
        OUTPUT_NAME "mxLogLibShared"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(mxLogLibShared PROPERTIES OUTPUT_NAME "mxLogLibSharedd")
endif ()

# 添加可执行程序，并链接静态库
add_executable(mxLogExample example/main.cpp
)
target_include_directories(mxLogExample PRIVATE include)
target_link_libraries(mxLogExample PRIVATE mxLogLib)  # 直接链接静态库

# 设置可执行程序的输出路径
set_target_properties(mxLogExample PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# 设置 pybind11 路径
list(APPEND CMAKE_PREFIX_PATH "D:/MyLibs/pybind11")
find_package(pybind11 REQUIRED)
add_subdirectory(python_module)

# 安装规则：将生成的 dll 和 lib 文件复制到项目源码目录的 lib 文件夹
install(TARGETS mxLogLib mxLogLibShared mxLogExample
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib
)
