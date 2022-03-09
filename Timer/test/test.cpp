#include <catch2/catch_test_macros.hpp>
#include "../include/Timer.h"

TEST_CASE("NewTimerValid"){
    m1::Timer timer = m1::Timer();
    REQUIRE_FALSE(&timer == nullptr);
}