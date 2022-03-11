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

        void Log(Log log){
            for(int i = 0; i < logDestinations.size(); ++i){
                logDestinations[i]->Log(log);
            }
        }

        std::vector<std::shared_ptr<ILogDestination>> LogDestinations(){
           return logDestinations;
        }
        private:

        std::vector<std::shared_ptr<ILogDestination>> logDestinations;
    };
}