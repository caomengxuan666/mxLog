from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import subprocess
import sys
import os
import logging

# 配置日志
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        # 直接指定源文件路径
        source_files = [
            "D:/study/mxLog/src/SimpleFormatter.cpp",
            "D:/study/mxLog/src/console_appender.cpp",
            "D:/study/mxLog/src/async_logger.cpp",
            "D:/study/mxLog/src/file_appender.cpp",
        ]

        include_dirs = ["D:/study/mxLog/include"]  # 指定头文件路径
        extra_compile_args = ["-std=c++17"]

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            "-DCMAKE_BUILD_TYPE=Release",
            "-DCMAKE_CXX_STANDARD=17",
            f"-DCMAKE_INCLUDE_PATH={' '.join(include_dirs)}",
        ]

        build_args = ["--config", "Release"]

        if sys.platform == "win32":
            cmake_args += ["-A", "x64"]

        # 构建 CMake
        build_temp = os.path.abspath(self.build_temp)
        os.makedirs(build_temp, exist_ok=True)
        try:
            subprocess.check_call(["cmake", ext.sourcedir] + cmake_args, cwd=build_temp)
            subprocess.check_call(["cmake", "--build", "."] + build_args, cwd=build_temp)
        except subprocess.CalledProcessError as e:
            logger.error(f"Error during build: {e}")
            sys.exit(1)


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


setup(
    name='mxLogPy',
    version='0.1.11',
    author='cmx',
    author_email='2507560089@qq.com',
    description='High Performance and multi-thread & async Log Library by C++',
    long_description=open('README.md', encoding='utf-8').read(),
    long_description_content_type='text/markdown',
    url='https://github.com/caomengxuan666/mxLog',
    ext_modules=[CMakeExtension('mxLogPy', sourcedir='.')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
    install_requires=['pybind11'],
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
)
