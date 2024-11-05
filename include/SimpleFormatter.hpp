//
// Created by CaoMengxuan on 2024/11/5.
//

#ifndef SETUP_PY_SIMPLEFORMATTER_HPP
#define SETUP_PY_SIMPLEFORMATTER_HPP
#include "formatter.hpp"

namespace cmx::Log {

class SimpleFormatter : public Formatter {
public:
    std::string format(const std::string& message, LogLevel level) const override;
};

}


#endif//SETUP_PY_SIMPLEFORMATTER_HPP
