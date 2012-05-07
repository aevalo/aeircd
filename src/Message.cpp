#include <boost/regex.hpp>
#include "aeircd.hpp"

namespace aeircd
{
  namespace Message
  {
    bool ParsePrefix(const std::string& str, Prefix& p)
    {
      AEIRCD_ENTER_FUNC;
      
      bool ret = false;
      try
      {
        std::string s("Parsing prefix: ");
        s += str;
        AEIRCD_LOG_DEBUG(s);
        
        boost::match_results<std::string::const_iterator> what;
        boost::regex expression("(!(\\w+))?(@(\\w+))?", boost::regex::perl);
        std::string::const_iterator start = str.begin(), end = str.end(); 
        ret = boost::regex_search(start, end, what, expression);
        
        // what[0] contains the whole string
        // what[1] contains the username with ! prefix
        // what[2] contains just the username
        // what[3] contains the hostname with ! prefix
        // what[4] contains just the hostname
        if (what.size() >= 5 && what[1].matched)
        {
          p.user = std::string(what[2].first, what[2].second);
          std::string s("Username: ");
          s += p.user;
          AEIRCD_LOG_DEBUG(s);
        }
        if (what.size() >= 5 && what[2].matched)
        {
          p.host = std::string(what[4].first, what[4].second);
          std::string s("Hostname: ");
          s += p.host;
          AEIRCD_LOG_DEBUG(s);
        }
      }
      catch (std::exception& e)
      {
        std::string s("Error: ");
        s += e.what();
        AEIRCD_LOG_WARNING(s);
        AEIRCD_LEAVE_FUNC;
        return false;
      }
      
      AEIRCD_LEAVE_FUNC;
      return ret;
    }
  }
}
