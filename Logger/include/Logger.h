#pragma once
#include "ILogDestination.h"

namespace m1{
    class Logger{
        public:
        
        void AddLogDestination(std::shared_ptr<ILogDestination> logDest){
            logDestinations.push_back(logDest);
        }

        std::vector<std::shared_ptr<ILogDestination>> LogDestinations(){
           return logDestinations;
        }

        private:

        std::vector<std::shared_ptr<ILogDestination>> logDestinations;
    };
}