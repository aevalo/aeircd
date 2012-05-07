#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "aeircd.hpp"



int main( int argc, const char* argv[] )
{
  aeircd::Initialize();
  
  std::string home_dir;
  std::string system_conf_dir;
  std::string log_file_dir;
  
  aeircd::SysDep::GetHomePath( home_dir );
  aeircd::SysDep::GetSystemConfigPath( system_conf_dir );
  aeircd::SysDep::GetLogFilePath( log_file_dir );
  
  std::cout << "Current home path is " << home_dir << std::endl;
  std::cout << "System configuration path is " << system_conf_dir << std::endl;
  std::cout << "Log file path is " << log_file_dir << std::endl;
  
  AEIRCD_LOG_TRACE( "Trace message" );
  AEIRCD_LOG_DEBUG( "Debug message" );
  AEIRCD_LOG_WARNING( "Warning message" );
  AEIRCD_LOG_CRITICAL( "Critical message" );
  AEIRCD_LOG_FATAL( "Fatal message" );
  
  aeircd::pLogger->logLevel( aeircd::Logger::Logger::All );
  
  AEIRCD_LOG_TRACE( "Trace message" );
  AEIRCD_LOG_DEBUG( "Debug message" );
  AEIRCD_LOG_WARNING( "Warning message" );
  AEIRCD_LOG_CRITICAL( "Critical message" );
  AEIRCD_LOG_FATAL( "Fatal message" );
  
  aeircd::pLogger->logLevel( aeircd::Logger::Logger::None );
  
  AEIRCD_LOG_TRACE( "Trace message" );
  AEIRCD_LOG_DEBUG( "Debug message" );
  AEIRCD_LOG_WARNING( "Warning message" );
  AEIRCD_LOG_CRITICAL( "Critical message" );
  AEIRCD_LOG_FATAL( "Fatal message" );
  
  aeircd::pLogger->logLevel( aeircd::Logger::Logger::Debug );
  
  AEIRCD_ENTER_FUNC;
  AEIRCD_LEAVE_FUNC;
  
  aeircd::Message::Prefix p;
  bool ret = aeircd::Message::ParsePrefix("!user@host", p);
  if (ret)
  {
    std::cout << "Username: " << p.user << std::endl;
    std::cout << "Hostname: " << p.host << std::endl;
  }
  
  aeircd::Uninitialize();
  
  return 0;
}
