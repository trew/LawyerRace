#ifndef LWR_STRINGUTILS_HPP
#define LWR_STRINGUTILS_HPP

#include <string>

namespace StringUtils
{
  bool startsWith(const std::string& str, const std::string& start)
  {
    if (str.size() >= start.size())
    {
      return str.find(start) == 0;
    }

    return false;
  }
}

#endif