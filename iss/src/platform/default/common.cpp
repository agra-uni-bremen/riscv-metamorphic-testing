#include "common.h"

#include <cxxabi.h>

#include <boost/stacktrace.hpp>
#include <sstream>
#include <string>

TraceableException::TraceableException(std::string message) {
    std::ostringstream ss;
    ss << message << std::endl
       << boost::stacktrace::stacktrace();
    _what = ss.str();
}
const char* TraceableException::what() const noexcept {
    return _what.c_str();
}
