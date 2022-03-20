#include <catch2/catch_test_macros.hpp>
#include "Net/IPAddress.h"
#include "Net/SocketAddress.h"

TEST_CASE("SocketAddressIPAddressEqualsConstructorArg"){
    IPAddress addr("123.234.111.222");
    SocketAddress socketAddr(addr, 55);
    REQUIRE( addr.ToString() == socketAddr.IpAddress().ToString() );
}

TEST_CASE("SocketAddressPortEqualsContructorArg"){
    IPAddress addr("0000:0000:0000:0000:0000:0000:0000:0000");
    SocketAddress socketAddr(addr, 155);
    REQUIRE(155 == socketAddr.Port());
}

TEST_CASE("EqualSocketAddressesCompareEqualOperator"){
    SocketAddress a1(IPAddress("localhost"), 128);
    SocketAddress a2(IPAddress("127.0.0.1"), 128);

    REQUIRE(a1 == a2);
}