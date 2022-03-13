#pragma once
#include <string>
#include <sstream>

class Timestamp{
    public:

    Timestamp() = delete;

    Timestamp(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute){
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
    }

    std::string ToString(){
        std::stringstream ss;

        std::string dayString = day > 9 ? std::to_string(day) : std::string("0") + std::to_string(day);
        std::string monthString = month > 9 ? std::to_string(month) : std::string("0") + std::to_string(month);
        std::string minuteString = minute > 9 ? std::to_string(minute) : std::string("0") + std::to_string(minute);

        std::string hourString = hour > 12 ? std::to_string(hour-12) : std::to_string(hour);

        std::string amOrPm = hour > 12 ? "pm" : "am";

        ss << dayString << "/" << monthString << "/" << year << " " << hourString << ":" << minuteString <<amOrPm;
        return ss.str();
    }

    unsigned int Year(){
        return year;
    }

    unsigned int Month(){
        return month;
    }

    unsigned int Day(){
        return day;
    }

    unsigned int Hour(){
        return hour;
    }

    unsigned int Minute(){
        return minute;
    }

    private:

    unsigned int year; 
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
};