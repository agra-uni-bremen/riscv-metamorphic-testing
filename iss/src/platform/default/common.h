#pragma once
#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <string>
#include <vector>

#include "executor.h"

struct RuleCheckFailed : std::runtime_error {
    using runtime_error::runtime_error;
};
class TraceableException : std::exception {
    std::string _what;

   public:
    TraceableException(std::string message);
    const char *what() const noexcept override;
};
