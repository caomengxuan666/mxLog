#include "LogManager.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace cmx::Log;

PYBIND11_MODULE(mxLogPy, m) {
    m.doc() = "Python bindings for mxLog library";

    // 定义 LogLevel 枚举类型
    py::enum_<LogLevel>(m, "LogLevel")
            .value("Info", LogLevel::Info)
            .value("Warning", LogLevel::Warning)
            .value("Error", LogLevel::Error)
            .value("Fatal", LogLevel::Fatal)
            .value("Debug", LogLevel::Debug)
            .value("LogSystem", LogLevel::LogSystem)
            .export_values();

    // 导出 LogManager 单例类
    py::class_<LogManager>(m, "LogManager")
            .def_static("getInstance", &LogManager::getInstance, py::return_value_policy::reference)
            .def("setCurrentLevel", &LogManager::setCurrentLevel)
            .def("setFileAppender", &LogManager::setFileAppender)
            .def("setConsoleAppender", &LogManager::setConsoleAppender)
            .def("log", &LogManager::log, py::arg("level"), py::arg("message")) // 确保参数顺序
            .def("setOutBufferSize", &LogManager::setOutBufferSize)
            .def("setBufferSize", &LogManager::setBufferSize)
            .def("clearConsoleBuffer", &LogManager::clearConsoleBuffer)
            .def("setLoggerName", &LogManager::setLoggerName);
}
