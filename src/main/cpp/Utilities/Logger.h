#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Amber
{
    namespace Utilities
    {
        class Logger
        {
            public:
                enum Severity
                {
                    TRACE,
                    DEBUG,
                    INFO,
                    NOTICE,
                    WARNING,
                    ERROR,
                    CRITICAL,
                    FATAL
                };
                
                template <typename MessageType>
                inline void trace(const MessageType &message)    { log(message, TRACE);    }
                
                template <typename MessageType>
                inline void debug(const MessageType &message)    { log(message, DEBUG);    }
                
                template <typename MessageType>
                inline void info(const MessageType &message)     { log(message, INFO);     }
                
                template <typename MessageType>
                inline void notice(const MessageType &message)   { log(message, NOTICE);   }
                
                template <typename MessageType>
                inline void warning(const MessageType &message)  { log(message, WARNING);  }
                
                template <typename MessageType>
                inline void error(const MessageType &message)    { log(message, ERROR);    }
                
                template <typename MessageType>
                inline void critical(const MessageType &message) { log(message, CRITICAL); }
                
                template <typename MessageType>
                inline void fatal(const MessageType &message)    { log(message, FATAL);    }
                
                template <typename MessageType>
                inline void log(const MessageType &message, Severity severity)
                {
                    // FIXME implement proper logging
                }
        };
    }
}

#endif // LOGGER_H
