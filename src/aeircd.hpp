#ifndef AEIRCD_HPP_INCLUDED
#define AEIRCD_HPP_INCLUDED

#include <boost/current_function.hpp>
#include "SysDep.hpp"
#include "Logger.hpp"
#include "Message.hpp"

#define AEIRCD_ENTER_FUNC       {if(aeircd::pLogger){aeircd::pLogger->debug( std::string(">>> ") + std::string(BOOST_CURRENT_FUNCTION) ); }}
#define AEIRCD_LEAVE_FUNC       {if(aeircd::pLogger){aeircd::pLogger->debug( std::string("<<< ") + std::string(BOOST_CURRENT_FUNCTION) ); }}

#define AEIRCD_LOG_TRACE(msg)     {if(aeircd::pLogger){aeircd::pLogger->trace( msg );}}
#define AEIRCD_LOG_DEBUG(msg)     {if(aeircd::pLogger){aeircd::pLogger->debug( msg );}}
#define AEIRCD_LOG_WARNING(msg)   {if(aeircd::pLogger){aeircd::pLogger->warning( msg );}}
#define AEIRCD_LOG_CRITICAL(msg)  {if(aeircd::pLogger){aeircd::pLogger->critical( msg );}}
#define AEIRCD_LOG_FATAL(msg)     {if(aeircd::pLogger){aeircd::pLogger->fatal( msg );}}



namespace aeircd
{
  bool Initialize();
  bool Uninitialize();
  
  extern class Logger::Logger* pLogger;
}


#endif // AEIRCD_HPP_INCLUDED
