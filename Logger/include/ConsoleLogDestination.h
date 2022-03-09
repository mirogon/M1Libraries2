#pragma once 
#include <iostream>
#include "ILogDestination.h"

class ConsoleLogDestination : public m1::ILogDestination{
    public:

    void Log(m1::Log log){
        std::cout<<log.Message()<<std::endl;
    }
};
