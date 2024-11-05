from setuptools import setup, find_packages
from setuptools.extension import Extension
from setuptools.command.build_ext import build_ext as _build_ext
import pybind11
import sys
import os
import logging

os.environ['PYTHON_CONFIG_VARS'] = 'Py_DEBUG=0'

# 配置日志
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class build_ext(_build_ext):
    def build_extensions(self):
        try:
            if sys.platform == 'win32':
                # 对于 Windows，使用 MSVC 编译器
                for ext in self.extensions:
                    ext.extra_compile_args = ['/std:c++17']
            else:
                # 对于其他平台，使用 GCC 或 Clang 编译器
                for ext in self.extensions:
                    ext.extra_compile_args = ['-std=c++17']
            super().build_extensions()
        except Exception as e:
            logger.error(f"编译过程中发生错误: {e}")
            raise


# 获取当前目录
current_dir = os.path.abspath(os.path.dirname(__file__))

ext_modules = [
    Extension(
        'mxLogPy',  # 这里必须与 C++ 代码中的模块名称一致
        ['pybind_wrapper.cpp'],
        include_dirs=[
            pybind11.get_include(),
            os.path.join(current_dir, 'include')
        ],
        library_dirs=[
            os.path.join(current_dir, 'lib')
        ],
        libraries=['mxLogLib'],
        language='c++'
    ),
]

setup(
    name='mxLogPy',
    version='0.1.10',
    packages=find_packages(),
    package_data={
        'mxLogPy': ['*.pyd'],
    },
    include_package_data=True,
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext},
    install_requires=[
        'pybind11'
    ],
    description='High Performance and mutilThread & async Log Library by Cpp',
    long_description=open('README.md', encoding='utf-8').read(),
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
