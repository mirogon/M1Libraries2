#pragma once
#include <chrono>
#include "ITimeSource.h"

class StdTimeSource : public ITimeSource{
    public:

    Timestamp CurrentTime(){
        auto currentTime = std::chrono::system_clock::now();
		std::time_t time_t_time = std::chrono::system_clock::to_time_t(currentTime);
		tm* localTime = std::localtime(&time_t_time);

        Timestamp timeStamp(localTime->tm_year + 1900, localTime->tm_mon +1 , localTime->tm_mday, localTime->tm_hour, localTime->tm_min);
        return timeStamp;
    }
};