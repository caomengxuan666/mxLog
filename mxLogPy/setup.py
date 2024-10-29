from setuptools import setup, find_packages

setup(
    name='mxLogPy',
    version='0.1.0',
    packages=find_packages(),
    package_data={
        'mxLog_Package': ['*.pyd'],
    },
    include_package_data=True,
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
