#pragma once
#include <string>

namespace m1{
    
    enum class LogLevel{
        NONE = 0,
        WARNING = 2,
        ERROR = 3
    };

    class Log{
        public:

        Log() = delete;

        Log(const std::string& message, LogLevel level = LogLevel::NONE ){
            this->message = message;
            this->level = level;
        }
        
        const std::string& Message(){
            return message;
        }

        LogLevel Level(){
            return level;
        }

        private:

        std::string message;
        LogLevel level;
    };
}
