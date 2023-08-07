#pragma once

#include <string>

using namespace std;

static inline std::string lstrip(const std::string& s, const string& stripStr)
{
    size_t start = s.find_first_not_of(stripStr);
    return (start == std::string::npos) ? "" : s.substr(start);
}

static inline std::string rstrip(const std::string& s, const string& stripStr)
{
    size_t end = s.find_last_not_of(stripStr);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static inline std::string strip(const std::string& s, const string& stripStr = " \n\r\t\f\v") {
    return rstrip(lstrip(s, stripStr), stripStr);
}