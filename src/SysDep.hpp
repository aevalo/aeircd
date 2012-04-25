#ifndef AEIRCD_SYSDEP_HPP_INCLUDED
#define AEIRCD_SYSDEP_HPP_INCLUDED

#include <string>

namespace aeircd
{
  namespace SysDep
  {
#ifdef WIN32
    const char PATH_SEPARATOR = '\\';
#else
    const char PATH_SEPARATOR = '/';
#endif

    // Path to user home directory
    bool GetHomePath( std::string& path );
    
    // Path to system-wide configuration directory
    bool GetSystemConfigPath( std::string& path );
    
    // Path to logging directory
    bool GetLogFilePath( std::string& path );
  }
}

#endif // AEIRCD_SYSDEP_HPP_INCLUDED
