#include <catch2/catch_test_macros.hpp>
#include <thread>
#include "Timer/Timer.h"

TEST_CASE("NewTimerValid"){
    m1::Timer timer = m1::Timer();
    REQUIRE_FALSE(&timer == nullptr);
}

TEST_CASE("NewTimerTimeAboveZeroMicro"){
    m1::Timer timer = m1::Timer();
    REQUIRE(timer.ElapsedMicro() >= 0);
}

TEST_CASE("TimerAbove10MicroAfterWaiting11Micro"){
    m1::Timer timer = m1::Timer();
    std::this_thread::sleep_for(std::chrono::microseconds(11));
    REQUIRE(timer.ElapsedMicro() > 10);
}

TEST_CASE("TimerElapsedMilliEqualsWaitedTime"){
    m1::Timer timer = m1::Timer();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    REQUIRE(timer.ElapsedMilli() > 2);
    REQUIRE(timer.ElapsedMilli() < 100);
}

TEST_CASE("TimerElapsedSecIsZeroAfterInstantiation"){
    m1::Timer timer = m1::Timer();
    REQUIRE(timer.ElapsedSec() == 0);
}

TEST_CASE("TimerElapsedMilliAboutZeroAfterRestartingTimer"){
    m1::Timer timer = m1::Timer();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    REQUIRE(timer.ElapsedMilli() >= 50);
    timer.Restart();
    REQUIRE(timer.ElapsedMilli() <= 25);
}