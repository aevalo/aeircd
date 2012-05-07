#ifndef AEIRCD_MESSAGE_HPP_INCLUDED
#define AEIRCD_MESSAGE_HPP_INCLUDED

#include <string>
#include <boost/regex.hpp>

namespace aeircd
{
  namespace Message
  {
    struct Prefix
    {
      std::string user;
      std::string host;
    };
    
    bool ParsePrefix(const std::string& str, Prefix& p);
  }
}

#endif // AEIRCD_MESSAGE_HPP_INCLUDED
