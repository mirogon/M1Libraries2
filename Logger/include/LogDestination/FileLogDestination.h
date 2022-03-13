#pragma once
#include <fstream>
#include <iostream>
#include "ILogDestination.h"
#include "../Log.h"

class FileLogDestination : public m1::ILogDestination{

    public:

    FileLogDestination() = delete;
    FileLogDestination(std::string file){
        this->file = file;
    }

    void Log(m1::Log l){
        std::fstream fileStream;
        fileStream.exceptions(std::fstream::failbit | std::fstream::badbit);
        fileStream.open(file.c_str(), std::ios::out | std::ios::app);

        fileStream<<l.Time().ToString() << " | " << m1::LogLevelToString(l.Level()) << " | " <<l.Message()<<std::endl;

        fileStream.flush();
        fileStream.close();
    }

    private:
    std::string file;
    
};