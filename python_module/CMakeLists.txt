project(mxLogPy)

# 添加 Python 模块
pybind11_add_module(mxLogPy MODULE
    pybind_wrapper.cpp
)

# 根据构建类型设置不同的链接库
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(mxLogPy PRIVATE ../lib/mxLogLibd)
    target_compile_definitions(mxLogPy PRIVATE _DEBUG)
    target_compile_options(mxLogPy PRIVATE /MDd)
else()
    target_link_libraries(mxLogPy PRIVATE ../lib/mxLogLib)
    target_compile_definitions(mxLogPy PRIVATE NDEBUG)
    target_compile_options(mxLogPy PRIVATE /MD)
endif()

# 设置包含目录
target_include_directories(mxLogPy PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 关闭 Release 模式下的优化选项
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(mxLogPy PRIVATE /Od)  # 关闭优化
endif()
