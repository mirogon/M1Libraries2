#pragma once
#include <chrono>
#include "ITimeSource.h"

class StdTimeSource : public ITimeSource{
    public:

    Timestamp CurrentTime(){
        auto currentTime = std::chrono::system_clock::now();
		std::time_t time_t_time = std::chrono::system_clock::to_time_t(currentTime);
		tm* utcTime = std::gmtime(&time_t_time);

        Timestamp timeStamp(utcTime->tm_year + 1900, utcTime->tm_mon +1 , utcTime->tm_mday, utcTime->tm_hour, utcTime->tm_min);
        return timeStamp;
    }
};