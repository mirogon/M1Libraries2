#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>
#include "Logger/Logger.h"
#include "Logger/LogDestination/ILogDestination.h"
#include "Logger/LogDestination/ConsoleLogDestination.h"
#include "Logger/LogDestination/FileLogDestination.h"
#include "Logger/TimeSource/ITimeSource.h"

class TestLogDestination : public m1::ILogDestination{
    public:

    TestLogDestination(){
    }

    void Log(m1::Log l) override{
        logs.push_back(l);
    };

    std::vector<m1::Log> logs;
};

TEST_CASE("LogDestinationSizeIsOneAfterAddingOne"){
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest(new TestLogDestination());
    logger.AddLogDestination(logDest);
    REQUIRE(logger.LogDestinations().size() == 1);
}

TEST_CASE("LogCallsLogDestinationLog"){
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest(new TestLogDestination());
    logger.AddLogDestination(logDest);
    logger.Log("");
    TestLogDestination* tld = dynamic_cast<TestLogDestination*>(logDest.get());
    REQUIRE(tld->logs.size() == 1);
}

TEST_CASE("LogMessageIsSameAsLogArgument"){
    m1::Logger logger;
    std::shared_ptr<TestLogDestination> logDest(new TestLogDestination());
    logger.AddLogDestination(logDest);

    logger.Log("Hello, there!");

    REQUIRE(logDest->logs.back().Message() == "Hello, there!");
    REQUIRE_FALSE(logDest->logs.back().Message() == "NotRight");
}

TEST_CASE("NoLogDestinationsAfterRemoving"){
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest(new TestLogDestination());
    logger.AddLogDestination(logDest);
    logger.RemoveLogDestination(logDest);
    REQUIRE(logger.LogDestinations().size() == 0);
}

TEST_CASE("LogDestionationAtZeroEqualsAddedConsoleLogDestination"){
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest = std::make_shared<ConsoleLogDestination>(ConsoleLogDestination());
    logger.AddLogDestination(logDest);
    REQUIRE(logger.LogDestinations().at(0).get() == logDest.get());
}

TEST_CASE("LogLevelEqualsLogFunc"){
    std::shared_ptr<TestLogDestination> logDest = std::make_shared<TestLogDestination>(TestLogDestination());
    m1::Logger logger;
    logger.AddLogDestination(logDest);

    logger.Log("Info log");
    REQUIRE(logDest->logs.back().Level() == m1::LogLevel::NONE);

    logger.LogWarning("Warning log");
    REQUIRE(logDest->logs.back().Level() == m1::LogLevel::WARNING);

    logger.LogError("Error log");
    REQUIRE(logDest->logs.back().Level() == m1::LogLevel::ERROR);
}


class TestTimeSource : public ITimeSource{
    public:

    TestTimeSource(int year, int month, int day, int hour){
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
    }

    Timestamp CurrentTime(){
        Timestamp t(year, month, day, hour, 0);
        return t;
    }

    int year;
    int month;
    int day;
    int hour;
};

TEST_CASE("TimestampToStringEqualsLogtime"){
    std::shared_ptr<ITimeSource> timeSource = std::make_shared<TestTimeSource>(TestTimeSource(1999, 7, 26, 7));
    m1::Logger logger(timeSource);

    std::shared_ptr<TestLogDestination> logDest = std::make_shared<TestLogDestination>();
    logger.AddLogDestination(logDest);

    logger.Log("");

    REQUIRE(logDest->logs.back().Time().ToString() == "26/07/1999 7:00am");
}

TEST_CASE("StdTimestampCurrentTimeEqualsCurrentTime"){
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
    tm* localTime = std::localtime(&time);

    StdTimeSource timeSource;

    REQUIRE(localTime->tm_year + 1900 == timeSource.CurrentTime().Year());
    REQUIRE(localTime->tm_mon + 1 == timeSource.CurrentTime().Month());
    REQUIRE(localTime->tm_mday == timeSource.CurrentTime().Day());
    REQUIRE(localTime->tm_hour == timeSource.CurrentTime().Hour());
    REQUIRE(localTime->tm_min == timeSource.CurrentTime().Minute());
}

TEST_CASE("TestConsoleLog"){
    std::shared_ptr<ITimeSource> timeSource = std::make_shared<StdTimeSource>();
    m1::Logger logger(timeSource);

    std::shared_ptr<ConsoleLogDestination> logDest = std::make_shared<ConsoleLogDestination>();
    logger.AddLogDestination(logDest);

    std::shared_ptr<FileLogDestination> fileLogDest = std::make_shared<FileLogDestination>("test2.log");
    logger.AddLogDestination(fileLogDest);

    logger.Log("This is some log");
    logger.LogWarning("This is some warning log");
    logger.LogError("This is some error log");
}

TEST_CASE("FileLogDestinationInvalidFileNameThrowsException"){
    m1::Logger logger;
    std::shared_ptr<FileLogDestination> fileLogDest = std::make_shared<FileLogDestination>("<>:**");
    logger.AddLogDestination(fileLogDest);

    REQUIRE_THROWS(logger.Log("This should not be logged cause of an error"));
}

TEST_CASE("ExtremeValuesTimestampToStringDoesntThrow"){
    Timestamp t(INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX);
    REQUIRE_NOTHROW(t.ToString());
}

TEST_CASE("LogIsThreadSafe"){
    std::shared_ptr<ITimeSource> timeSource = std::make_shared<TestTimeSource>(2022, 3, 14, 8);
    m1::Logger logger(timeSource);

    std::shared_ptr<m1::ILogDestination> logDest = std::make_shared<FileLogDestination>("thread.log");
    logger.AddLogDestination(logDest);

    std::thread t1([&logger](){
        logger.Log("HelloThere");
    });

    std::thread t2([&logger](){
        logger.Log("GeneralKenobi");
    });

    std::thread t3([&logger](){
        logger.Log("AdditionToMyCollection");
    });

    t3.join();
    t2.join();
    t1.join();

    std::string logString = "";
    std::fstream fileStream("thread.log", std::ios::in);
    std::getline(fileStream, logString, '\0');
    fileStream.flush();
    fileStream.close();

    REQUIRE_FALSE(std::string::npos == logString.find("14/03/2022 8:00am | None | HelloThere"));
    REQUIRE_FALSE(std::string::npos == logString.find("14/03/2022 8:00am | None | GeneralKenobi"));
    REQUIRE_FALSE(std::string::npos == logString.find("14/03/2022 8:00am | None | AdditionToMyCollection"));
    REQUIRE(3 ==  std::count(logString.begin(), logString.end(), '\n'));

    std::filesystem::remove("thread.log");
}