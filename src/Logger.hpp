#ifndef AEIRCD_LOGGER_HPP_INCLUDED
#define AEIRCD_LOGGER_HPP_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>




namespace aeircd
{
  namespace Logger
  {
    class Logger
    {
      public: // Types
        
        enum LogLevel
        {
          None      = 0,
          Trace     = 1,
          Debug     = 2,
          Warning   = 3,
          Critical  = 4,
          Fatal     = 5,
          All       = 6
        };
        
      public: // Functions
        
        Logger( const std::string& file, std::ios::open_mode mode = std::ios::out );
        ~Logger();

        inline LogLevel logLevel() const { return mLogLevel; }
        void logLevel( LogLevel level );

        void trace( const std::string& msg );
        void debug( const std::string& msg );
        void warning( const std::string& msg );
        void critical( const std::string& msg );
        void fatal( const std::string& msg );
        
      private: // Data
        
        LogLevel      mLogLevel;
        std::ofstream mLogFile;
    };
  }
}

#endif // AEIRCD_LOGGER_HPP_INCLUDED
