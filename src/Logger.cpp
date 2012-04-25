#include "Logger.hpp"


namespace aeircd
{
  namespace Logger
  {
    enum LogLevelBits
    {
      NoneBit     = 0x0000,
      TraceBit    = 0x0001,
      DebugBit    = 0x0002,
      WarningBit  = 0x0004,
      CriticalBit = 0x0008,
      FatalBit    = 0x0100
    };


    Logger::Logger( const std::string& file, std::ios::open_mode mode )
    : mLogLevel( Trace ), mLogFile( file.c_str(), mode )
    {
      if ( mLogFile.fail() )
      {
        mLogLevel = Trace;
      }
    }

    Logger::~Logger()
    {
      if ( mLogFile.is_open() )
      {
        mLogFile.flush();
        mLogFile.close();
      }
    }

    void Logger::logLevel( LogLevel level )
    {
      if ( mLogFile.good() )
      {
        switch ( level )
        {
          case Trace:
            mLogLevel = static_cast<LogLevel>( TraceBit );
            break;
          case Debug:
            mLogLevel = static_cast<LogLevel>( TraceBit | WarningBit | DebugBit );
            break;
          case Warning:
            mLogLevel = static_cast<LogLevel>( TraceBit | WarningBit );
            break;
          case Critical:
            mLogLevel = static_cast<LogLevel>( TraceBit | DebugBit | WarningBit | CriticalBit );
            break;
          case Fatal:
            mLogLevel = static_cast<LogLevel>( TraceBit | DebugBit | WarningBit | CriticalBit | FatalBit );
            break;
          case All:
            mLogLevel = static_cast<LogLevel>( TraceBit | DebugBit | WarningBit | CriticalBit | FatalBit );
            break;
          default:
            mLogLevel = static_cast<LogLevel>( NoneBit );
        }
      }
      else
      {
        mLogLevel = Trace;
      }
    }

    void Logger::trace( const std::string& msg )
    {
      if ( mLogLevel & TraceBit )
      {
        mLogFile << "TRACE: " << msg << std::endl;
      }
    }

    void Logger::debug( const std::string& msg )
    {
      if ( mLogLevel & DebugBit )
      {
        mLogFile << "DEBUG: " << msg << std::endl;
      }
    }

    void Logger::warning( const std::string& msg )
    {
      if ( mLogLevel & WarningBit )
      {
        mLogFile << "WARNING: " << msg << std::endl;
      }
    }

    void Logger::critical( const std::string& msg )
    {
      if ( mLogLevel & CriticalBit )
      {
        mLogFile << "CRITICAL: " << msg << std::endl;
      }
    }

    void Logger::fatal( const std::string& msg )
    {
      if ( mLogLevel & FatalBit )
      {
        mLogFile << "FATAL: " << msg << std::endl;
      }
    }
  }
}
