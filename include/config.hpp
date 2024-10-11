#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>

namespace cmx::Log {

    class Config {
    public:
        void set(const std::string& key, const std::string& value);
        std::string get(const std::string& key) const;

    private:
        std::map<std::string, std::string> m_configMap;
    };

} // namespace cmx::Log

#endif // CONFIG_HPP
