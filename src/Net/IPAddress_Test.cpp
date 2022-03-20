#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>
#include "Net/IPAddress.h"

using namespace std;

TEST_CASE("IPAddressToStringEqualsConstructorParameter"){
    IPAddress addr("123.234.111.222");
    REQUIRE("123.234.111.222" == addr.ToString());
}

TEST_CASE("ValidateIPV4Addresses"){
    REQUIRE_THROWS(IPAddress("1"));
    REQUIRE_THROWS(IPAddress("111.111.111.0111"));
    REQUIRE_THROWS(IPAddress("256.0.0.0"));

    REQUIRE_NOTHROW(IPAddress("0.0.0.0"));
    REQUIRE_NOTHROW(IPAddress("127.0.0.1"));
    REQUIRE_NOTHROW(IPAddress("127.234.255.0"));
}

TEST_CASE("ValidateIPV6Addresses"){
    REQUIRE_NOTHROW(IPAddress("0000:0000:0000:0000:0000:0000:0000:0000"));
    REQUIRE_NOTHROW(IPAddress("1111:2222:3333:4444:5555:6666:7777:8888"));
    REQUIRE_NOTHROW(IPAddress("FFFF:AAAA:BBBB:CCCC:DDDD:EEEE:0000:8888"));
    REQUIRE_NOTHROW(IPAddress(":::::::"));
    REQUIRE_NOTHROW(IPAddress(":4444::::::"));

    REQUIRE_THROWS(IPAddress("0000:0000:0000:0000:0000:0000:0000:0000:0000"));
    REQUIRE_THROWS(IPAddress("GGGG:0000:0000:0000:0000:0000:0000:0000"));
    REQUIRE_THROWS(IPAddress("0000:0000:0000:0000:0000:0000:0000:00001"));
    REQUIRE_THROWS(IPAddress("00:0000:0000:0000:0000:0000:0000:0001"));
    REQUIRE_THROWS(IPAddress("0000:0000:000:0000:0000:0000:0000:0001"));
    REQUIRE_THROWS(IPAddress("0000:0000:00000:0000:0000:0000:0000:0001"));
}

TEST_CASE("LocalHostIPV4IsValid"){
    REQUIRE_NOTHROW(IPAddress("localhost"));
    IPAddress addr("localhost");
    REQUIRE("127.0.0.1" == addr.ToString());
}

TEST_CASE("LocalHostIPV6IsValid"){
    REQUIRE_NOTHROW(IPAddress("::1"));
    IPAddress addr("::1");
    REQUIRE("0000:0000:0000:0000:0000:0000:0000:0001" == addr.ToString());
}

TEST_CASE("IPAddressIPV4AddressesEqualToString"){
    std::string cache = "";
    for(uint8_t i = 0; i < 255; ++i){
        cache = std::to_string(i) + ".0.0.0";
        IPAddress addr4(cache);
        REQUIRE(cache == addr4.ToString());
    }
    for(uint8_t i = 0; i < 255; ++i){
        cache = std::to_string(i) + "." + std::to_string(i) + "." + std::to_string(i) + "." + std::to_string(i);
        IPAddress addr4(cache);
        REQUIRE(cache == addr4.ToString());
    }
}

TEST_CASE("IPAddressIPV6AddressesEqualToString"){
    std::string cache = "";
    for(int i = 0; i < 16; ++i){
        for(int j = 0; j < 8; ++j){
            for(int k = 0; k < 4; ++k){
                cache += IPAddress::IntToHexaDigit(i);
            }
            cache += ":";
        }
        cache.pop_back();
        REQUIRE(cache == IPAddress(cache).ToString());
        cache = "";
    }
}

TEST_CASE("IPV6StringWithEmptyPartsEqualWholeString"){
    REQUIRE_NOTHROW(IPAddress("0000:0000:0000:0000:0000:0000::0000"));
    REQUIRE("0000:0000:0000:0000:0000:0000:0000:0000" == IPAddress("0000:0000:0000:0000:0000:0000::0000").ToString());

    REQUIRE_NOTHROW(IPAddress(":::::::"));
    REQUIRE("0000:0000:0000:0000:0000:0000:0000:0000" == IPAddress(":::::::").ToString());
    REQUIRE("0000:0000:0000:FFFF:0000:0000:0000:0000" == IPAddress(":::FFFF::::").ToString());
}


TEST_CASE("AddressFamilyReturnsCorrectAddressFamily"){
    IPAddress addr("192.168.0.1");
    REQUIRE(AddressFamily::IPV4 == addr.AddrFamily());

    IPAddress addrv6("0000:0000:0000:AAAA:0000:FFFF:0000:0000");
    REQUIRE(AddressFamily::IPV6 == addrv6.AddrFamily());
}

TEST_CASE("TwoEqualIPAddressesAreEqual"){
    IPAddress addr("128.100.200.0");
    IPAddress addr2("128.100.200.0");
    REQUIRE(addr == addr2);
}

TEST_CASE("TwoUnequalIPAddressesArentEqual"){
    IPAddress addr("0000:0000:0000:0000:0000:0000:0000:0000");
    IPAddress addr2("0000:0000:0000:0000:0000:0000:0000:0000");
    IPAddress addr3("0000:FFFF:0000:0000:0000:0000:0000:0000");

    REQUIRE(addr == addr2);
    REQUIRE_FALSE(addr == addr3);
}