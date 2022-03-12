#pragma once
#include <string>
#include <sstream>

class Timestamp{
    public:

    Timestamp() = delete;

    Timestamp(int year, int month, int day, int hour, int minute){
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

    int Year(){
        return year;
    }

    int Month(){
        return month;
    }

    int Day(){
        return day;
    }

    int Hour(){
        return hour;
    }

    int Minute(){
        return minute;
    }

    private:

    int year; 
    int month;
    int day;
    int hour;
    int minute;
};