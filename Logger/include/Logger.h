#pragma once
#include "ILogDestination.h"
#include "ConsoleLogDestination.h"

namespace m1{
    class Logger{
        public:
        
        void AddLogDestination(std::shared_ptr<ILogDestination> logDest){
            logDestinations.push_back(logDest);
        }

        void RemoveLogDestination(std::shared_ptr<ILogDestination> logDest){
            for(auto i = logDestinations.begin(); i != logDestinations.end(); ++i){
                if(i->get() == logDest.get()){
                    logDestinations.erase(i);
                    break;
                } 
            }
        }

        void Log(const std::string& message){
            LogImpl(message, m1::LogLevel::NONE);
        }

        void LogWarning(const std::string& message){
            LogImpl(message, m1::LogLevel::WARNING);
        }

        void LogError(const std::string& message){
            LogImpl(message, m1::LogLevel::ERROR);
        }

        std::vector<std::shared_ptr<ILogDestination>> LogDestinations(){
           return logDestinations;
        }
        private:

        void LogImpl(const std::string& message, m1::LogLevel level){
            m1::Log log = m1::Log(message, level);
            for(int i = 0; i < logDestinations.size(); ++i){
                logDestinations[i]->Log(log);
            }
        }

        std::vector<std::shared_ptr<ILogDestination>> logDestinations;
    };
}