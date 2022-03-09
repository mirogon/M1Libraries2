#pragma once
#include <string>

namespace m1{
    class Log{
        public:

        Log(){
            logMessage = "";
        }

        Log(const std::string& message){
            logMessage = message;
        }

        const std::string& Message(){
            return logMessage;
        }

        private:

        std::string logMessage;
    };
}
