#include <catch2/catch_test_macros.hpp>
#include "../include/Logger.h"
#include "../include/ConsoleLogDestination.h"
#include "../include/FileLogDestination.h"
#include <memory>
#include <filesystem>

class TestLogDestination : public m1::ILogDestination{
    public:

    TestLogDestination(){
    }

    void Log(m1::Log l) override{
        logs.push_back(l);
    };

    std::vector<m1::Log> logs;
};

TEST_CASE("NewLoggerIsValid"){
    m1::Logger logger;
    REQUIRE_FALSE(&logger == nullptr);
}

TEST_CASE("LogMessageEqualsConstructorArgument"){
    std::string msg = "This is a log message!";
    m1::Log log(msg);
    REQUIRE(log.Message() == msg);
    REQUIRE_FALSE(log.Message() == "NotRight");
}

TEST_CASE("CreateTestLogDestination"){
    m1::ILogDestination* logDest = new TestLogDestination();
    REQUIRE_FALSE(logDest == nullptr);
}

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
    logger.Log(m1::Log());
    TestLogDestination* tld = dynamic_cast<TestLogDestination*>(logDest.get());
    REQUIRE(tld->logs.size() == 1);
}

TEST_CASE("LogMessageIsSameAsLogArgument"){
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest(new TestLogDestination());
    logger.AddLogDestination(logDest);
    std::string logMsg = "Hello, There!";
    logger.Log(m1::Log(logMsg));
    TestLogDestination* tld = dynamic_cast<TestLogDestination*>(logDest.get());
    REQUIRE(tld->logs.back().Message() == logMsg);
    REQUIRE_FALSE(tld->logs.back().Message() == "NotRight");
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

TEST_CASE("FileExistsAfterLoggingToFileLogDestination"){
    std::filesystem::remove("test.log");
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest = std::make_shared<FileLogDestination>(FileLogDestination("test.log"));
    logger.AddLogDestination(logDest);
    logger.Log("Hello, there");

    REQUIRE(std::filesystem::exists("test.log") == true);

    std::filesystem::remove("test.log");
}

TEST_CASE("FileContentEqualsLogString"){
    std::filesystem::remove("test.log");
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest = std::make_shared<FileLogDestination>(FileLogDestination("test.log"));
    logger.AddLogDestination(logDest);
    logger.Log("Hello, there");

    std::string readContent = "";
    std::fstream fileStream = std::fstream("test.log", std::ios::in);
    std::getline(fileStream, readContent);
    fileStream.close();

    REQUIRE("Hello, there" == readContent);

    std::filesystem::remove("test.log");

}



TEST_CASE("LogWorksWithStringRValue"){
    m1::Logger logger;
    logger.Log("Hello C String log");
}