# python_module/CMakeLists.txt
project(mxLogPy)

# 添加 Python 模块
pybind11_add_module(mxLogPy MODULE
    pybind_wrapper.cpp
)

# 将 mxLogLib 链接到 Python 模块中
target_link_libraries(mxLogPy PRIVATE mxLogLib)

# 根据构建类型设置不同的链接库
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(mxLogPy PRIVATE ../lib/mxLogLibd)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(mxLogPy PRIVATE ../lib/mxLogLib)
endif()

# 设置包含目录
target_include_directories(mxLogPy PRIVATE ${CMAKE_SOURCE_DIR}/include)

