//
// Created by CaoMengxuan on 2024/10/11.
//
// config.cpp

#include "config.hpp"

namespace cmx::Log {

    void Config::set(const std::string& key, const std::string& value) {
        m_configMap[key] = value;
    }

    std::string Config::get(const std::string& key) const {
        auto it = m_configMap.find(key);
        if (it != m_configMap.end()) {
            return it->second;
        }
        return ""; // 返回空字符串或抛出异常，取决于需求
    }

} // namespace cmx::Log
