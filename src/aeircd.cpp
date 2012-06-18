#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <vector>
#include "aeircd.hpp"


namespace aeircd
{
  class Logger::Logger* pLogger = NULL;
  
  bool Initialize()
  {
    std::string filepath;
    SysDep::GetLogFilePath( filepath );
    filepath += "aeircd.log";
    pLogger = new Logger::Logger( filepath );
#ifdef _DEBUG
    pLogger->logLevel( Logger::Logger::All );
#endif
    
    using boost::property_tree::ptree;
    ptree pt;

    SysDep::GetSystemConfigPath( filepath );
    filepath += "aeircd.conf";
    read_xml(filepath, pt);

    std::string m_file = pt.get<std::string>("debug.filename");
    AEIRCD_LOG_DEBUG( m_file );
    int m_level = pt.get("debug.level", 0);
    char buf[10];
    sprintf(buf,"%d",m_level);
    AEIRCD_LOG_DEBUG( buf );
    std::vector<std::string> m_modules;
    BOOST_FOREACH(ptree::value_type &v,
            pt.get_child("debug.modules"))
    {
      AEIRCD_LOG_DEBUG(v.second.data());
      m_modules.push_back(v.second.data());
    }
    return true;
  }
  
  bool Uninitialize()
  {
    if ( pLogger )
    {
      delete pLogger;
      pLogger = NULL;
    }
    return true;
  }
}
