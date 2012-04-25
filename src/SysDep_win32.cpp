#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include "SysDep.hpp"


namespace aeircd
{
  namespace SysDep
  {
    void GetLastErrorMessageA( DWORD dwErrorId, std::string& error_msg )
    {
      LPVOID lpMsgBuf;
      
      DWORD dwRet = FormatMessage(
                      FORMAT_MESSAGE_ALLOCATE_BUFFER |
                      FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL,
                      dwErrorId,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      (LPTSTR) &lpMsgBuf,
                      0, NULL );
      if ( dwRet != 0 )
      {
        error_msg = static_cast<char*>( lpMsgBuf );
      }
      
      LocalFree(lpMsgBuf);
    }
    
    void GetLastErrorMessageW( DWORD dwErrorId, std::wstring& error_msg )
    {
      LPVOID lpMsgBuf;
      
      DWORD dwRet = FormatMessage(
                      FORMAT_MESSAGE_ALLOCATE_BUFFER |
                      FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL,
                      dwErrorId,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      (LPTSTR) &lpMsgBuf,
                      0, NULL );
      if ( dwRet != 0 )
      {
        error_msg = static_cast<wchar_t*>( lpMsgBuf );
      }
      
      LocalFree(lpMsgBuf);
    }
    
    
    // Path to user home directory
    bool GetHomePath( std::string& path )
    {
      char szBuffer[ MAX_PATH ];
      ZeroMemory( szBuffer, MAX_PATH );
      
      DWORD dwRet = ExpandEnvironmentStringsA( "%USERPROFILE%", szBuffer, MAX_PATH );
      if ( dwRet == 0 )
      {
        dwRet = ExpandEnvironmentStringsA( "%HOMEDRIVE%", szBuffer, MAX_PATH );
        if ( dwRet == 0 )
        {
          return false;
        }
        path = szBuffer;
        dwRet = ExpandEnvironmentStringsA( "%HOMEPATH%", szBuffer, MAX_PATH );
        if ( dwRet == 0 )
        {
          return false;
        }
        path += szBuffer;
      }
      else
      {
        path = szBuffer;
      }
      if ( path.at( path.length() - 1 ) != PATH_SEPARATOR )
      {
          path += PATH_SEPARATOR;
      }
      return true;
    }
    
    // Path to system-wide configuration directory
    bool GetSystemConfigPath( std::string& path )
    {
      // We are calling ANSI version of the function, so it's safe to use char
      char szFilename[ MAX_PATH ];
      ZeroMemory( szFilename, MAX_PATH );
      
      // Since we are working with ANSI version of string class,
      // make sure we call ANSI version of GetModuleFileName
      DWORD dwRet = GetModuleFileNameA( NULL, szFilename, MAX_PATH );
      if ( dwRet == 0 || dwRet == MAX_PATH )
      {
        DWORD dwLastError = GetLastError();
        std::string error_msg;
        GetLastErrorMessageA( dwLastError, error_msg );
      }
      
      std::string fn( szFilename );
      
      // Find the position of <app install path>\aeircd,
      // by subtracting 3 (for bin) from last \ of the path
      std::size_t pos = fn.find_last_of( PATH_SEPARATOR ) - 3;
      path  = fn.substr( 0, pos );
      path += "config";
      path += PATH_SEPARATOR;
      return true;
    }
    
    // Path to logging directory
    bool GetLogFilePath( std::string& path )
    {
      // We are calling ANSI version of the function, so it's safe to use char
      char szFilename[ MAX_PATH ];
      ZeroMemory( szFilename, MAX_PATH );
      
      // Since we are working with ANSI version of string class,
      // make sure we call ANSI version of GetModuleFileName
      DWORD dwRet = GetModuleFileNameA( NULL, szFilename, MAX_PATH );
      if ( dwRet == 0 || dwRet == MAX_PATH )
      {
        DWORD dwLastError = GetLastError();
        std::string error_msg;
        GetLastErrorMessageA( dwLastError, error_msg );
      }
      
      std::string fn( szFilename );
      
      // Find the position of <app install path>\aeircd,
      // by subtracting 3 (for bin) from last \ of the path
      std::size_t pos = fn.find_last_of( PATH_SEPARATOR ) - 3;
      path  = fn.substr( 0, pos );
      path += "logs";
      path += PATH_SEPARATOR;
      return true;
    }
  }
}
