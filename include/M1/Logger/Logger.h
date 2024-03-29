#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include "LogDestination/ILogDestination.h"
#include "LogDestination/ConsoleLogDestination.h"
#include "TimeSource/StdTimeSource.h"

namespace m1{
    class Logger{
        public:

        Logger(std::shared_ptr<ITimeSource> timeSource = std::make_shared<StdTimeSource>()){
            this->timeSource = timeSource;
        }

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
            LogImpl(message, m1::LogLevel::LL_NONE);
        }

        void LogWarning(const std::string& message){
            LogImpl(message, m1::LogLevel::LL_WARNING);
        }

        void LogError(const std::string& message){
            LogImpl(message, m1::LogLevel::LL_ERROR);
        }

        std::vector<std::shared_ptr<ILogDestination>> LogDestinations(){
           return logDestinations;
        }
        private:

        void LogImpl(const std::string& message, m1::LogLevel level){
            std::lock_guard<std::mutex> lgMutex(mutex);
            m1::Log log = m1::Log(message, timeSource->CurrentTime(), level);
            for(int i = 0; i < logDestinations.size(); ++i){
                logDestinations[i]->Log(log);
            }
        }

        std::mutex mutex;
        std::shared_ptr<ITimeSource> timeSource;
        std::vector<std::shared_ptr<ILogDestination>> logDestinations;
    };
}