#include <catch2/catch_test_macros.hpp>
#include "../include/Logger.h"
#include <memory>

class TestLogDestination : public m1::ILogDestination{
    public:
    void Log(m1::Log l) override{

    };
};

TEST_CASE("NewLoggerIsValid"){
    m1::Logger logger;
    REQUIRE_FALSE(&logger == nullptr);
}

TEST_CASE("LogMessageEqualsConstructorArgument"){
    std::string msg = "This is a log message!";
    m1::Log log(msg);
    REQUIRE(log.Message() == msg);
}

TEST_CASE("CreateTestLogDestination"){
    m1::ILogDestination* logDest = new TestLogDestination();
    REQUIRE_FALSE(logDest == nullptr);
}

TEST_CASE("AddLogDestination"){
    m1::Logger logger;
    std::shared_ptr<m1::ILogDestination> logDest(new TestLogDestination());
    logger.AddLogDestination(logDest);
    REQUIRE(logger.LogDestinations().size() == 1);
}
