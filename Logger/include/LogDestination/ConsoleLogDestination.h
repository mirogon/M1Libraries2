#pragma once 
#include <iostream>
#include "ILogDestination.h"

class ConsoleLogDestination : public m1::ILogDestination{
    public:

    void Log(m1::Log log){
        std::cout<<log.Time().ToString() << " | " << m1::LogLevelToString(log.Level()) << " | " <<log.Message()<<std::endl;
    }
};
