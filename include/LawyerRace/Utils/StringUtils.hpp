#ifndef LWR_STRINGUTILS_HPP
#define LWR_STRINGUTILS_HPP

#include <string>

namespace StringUtils
{
  bool startsWith(const std::string& str, const std::string& start)
  {
    if (str.size() < start.size())
    {
      return false;
    }

    std::string::const_iterator itStr = str.cbegin();
    std::string::const_iterator itStart = start.cbegin();

    while (itStart != start.cend())
    {
      if (itStr == str.cend())
      {
        return false;
      }

      if ((*itStart) != (*itStr))
      {
        return false;
      }

      itStart++;
      itStr++;
    }

    return true;
  }
}

#endif