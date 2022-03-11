#pragma once
#include "ILogDestination.h"
#include "Log.h"
#include <fstream>

class FileLogDestination : public m1::ILogDestination{

    public:

    FileLogDestination() = delete;
    FileLogDestination(std::string file){
        this->file = file;
    }

    void Log(m1::Log l){
        std::fstream fileStream = std::fstream(file.c_str(), std::ios::out);
        fileStream<<l.Message()<<std::endl;
        fileStream.flush();
        fileStream.close();
    }

    private:
    std::string file;
    
};