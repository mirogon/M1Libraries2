#pragma once
#include <string>
#include "Timestamp.h"

namespace m1{
    
    enum class LogLevel{
        NONE = 0,
        WARNING = 2,
        ERROR = 3
    };

    inline std::string LogLevelToString(LogLevel l){
        switch(l){
            case LogLevel::NONE: return "None";
            case LogLevel::WARNING: return "Warning";
            case LogLevel::ERROR: return "Error";
        }
    }

    class Log{
        public:

        Log() = delete;

        Log(const std::string& message, Timestamp timeStamp, LogLevel level = LogLevel::NONE):
            timeStamp{timeStamp}
        {
            this->message = message;
            this->level = level;
        }
        
        const std::string& Message(){
            return message;
        }

        LogLevel Level(){
            return level;
        }

        Timestamp Time(){
            return timeStamp;
        }

        private:

        std::string message;
        LogLevel level;
        Timestamp timeStamp;
    };
}
