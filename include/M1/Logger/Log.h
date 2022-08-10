#pragma once
#include <string>
#include "Timestamp.h"

namespace m1{
    
    enum class LogLevel{
        LL_NONE = 0,
        LL_WARNING = 2,
        LL_ERROR = 3
    };

    inline std::string LogLevelToString(LogLevel l){
        switch(l){
            case LogLevel::LL_NONE: return "None";
            case LogLevel::LL_WARNING: return "Warning";
            case LogLevel::LL_ERROR: return "Error";
        }
    }

    class Log{
        public:

        Log() = delete;

        Log(const std::string& message, Timestamp timeStamp, LogLevel level = LogLevel::LL_NONE):
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
