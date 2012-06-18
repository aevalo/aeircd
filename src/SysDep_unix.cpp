#include <cerrno>
#include <pwd.h>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <string>
#include "SysDep.hpp"


namespace aeircd
{
  namespace SysDep
  {
    // Path to user home directory
    bool GetHomePath( std::string& path )
    {
      char* home = ::getenv( "HOME" );
      if ( home == NULL )
      {
        struct passwd *pw = getpwuid( getuid() );
        if ( pw == NULL )
        {
          // Get the error string, with global errno
          char * error_msg = strerror( errno );
          return false;
        }
        path = pw->pw_dir;
        if ( path.at( path.length() - 1 ) != PATH_SEPARATOR )
        {
          path += PATH_SEPARATOR;
        }
        return true;
      }
      path = home;
      if ( path.at( path.length() - 1 ) != PATH_SEPARATOR )
      {
        path += PATH_SEPARATOR;
      }
      return true;
    }
    
    // Path to system-wide configuration directory
    bool GetSystemConfigPath( std::string& path )
    {
      // We are in Unix/Linux, use something like /etc/aeircd/
      path = "/etc/aeircd/";
      return true;
    }
    
    // Path to logging directory
    bool GetLogFilePath( std::string& path )
    {
      // We are in Unix/Linux, use something like /var/log/aeircd/
      path = "/var/log/aeircd/";
      return true;
    }
  }
}
