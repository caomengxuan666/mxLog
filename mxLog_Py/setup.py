from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext as _build_ext
import pybind11
import sys
import os

class build_ext(_build_ext):
    def build_extensions(self):
        if sys.platform == 'win32':
            # 对于 Windows，使用 MSVC 编译器
            for ext in self.extensions:
                ext.extra_compile_args = ['/std:c++17']
        else:
            # 对于其他平台，使用 GCC 或 Clang 编译器
            for ext in self.extensions:
                ext.extra_compile_args = ['-std=c++17']
        super().build_extensions()

# 获取当前目录的父目录，以便找到 include 和 lib 目录
parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

ext_modules = [
    Extension(
        'mxLogPy',  # 这里必须与 C++ 代码中的模块名称一致
        ['../python_module/pybind_wrapper.cpp'],  # 你的 C++ 文件名为 pybind_wrapper.cpp
        include_dirs=[
            pybind11.get_include(),
            os.path.join(parent_dir, 'include')  # 假设 LogManager.hpp 在 ../include 目录下
        ],
        library_dirs=[
            os.path.join(parent_dir, 'lib')  # 假设库文件在 ../lib 目录下
        ],
        libraries=['mxLogLib'],  # 假设库文件名为 mxLog.lib
        language='c++'
    ),
]

setup(
    name='mxLog_Py',
    version='0.1.0',
    packages=find_packages(),
    package_data={
        'mxLog_Py': ['*.pyd'],
    },
    include_package_data=True,
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext},
    install_requires=[
        # 我没有依赖项
    ],
    description='这是一高性能，多线程异步C++日志库的API包',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    author='cmx',
    author_email='2507560089@qq.com',
    url='https://github.com/caomengxuan666/mxLog',
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
)
