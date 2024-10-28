# python_module/CMakeLists.txt
project(mxLogPy)

# 添加 Python 模块
pybind11_add_module(mxLogPy MODULE
        ../include/LogManager.hpp
)

# 将 mxLogLib 链接到 Python 模块中
target_link_libraries(mxLogPy PRIVATE mxLogLib)
target_include_directories(mxLogPy PRIVATE ${CMAKE_SOURCE_DIR}/include)
