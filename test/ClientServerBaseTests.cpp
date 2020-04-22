#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "ClientServerBase.hpp"

using namespace clientServer;
using namespace boost::asio;

TEST_CASE("ClientServerBase get_ip tests") {
  auto base = ClientServerBase{};

  SECTION("returns IP address") {

    SECTION("returns IP if IPv4 and properly parsed") {
      auto ip = ip::address_v4{};
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v4>(""));
      REQUIRE(ip.any() == ip::address_v4());
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v4>("0.0.0.0"));
      REQUIRE(ip.any() == ip::address_v4());
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v4>("0.1.2.3"));
      REQUIRE(ip.any() == ip::address_v4());
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v4>("127.0.0.1"));
      REQUIRE(ip.any() == ip::address_v4());
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v4>("127.5.78.1"));
      REQUIRE(ip.any() == ip::address_v4());
    }

    SECTION("returns IP if IPv6 and properly parsed") {
      auto ip = ip::address_v6{};
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v6>(""));
      REQUIRE(ip.any() != ip::address_v6());
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v6>("fe80::4abd:ee8:f318:9528"));
      REQUIRE(ip.any() == ip::address_v6());
    }
  }

  SECTION("throw if invalid IP address format") {

    SECTION("throw if IPv4 and not parsed") {
      using inv_arg = std::invalid_argument;
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("0"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("127.0.0"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>(".0.0.4"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("127.0.0.d"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("127..0.qwe"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("145.4.0.12w"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("127.0.0.465"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("0127.0.0.465"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("0127..0.465"), inv_arg);
    }

    SECTION("throw if IPv6 and not parsed") {
      using inv_arg = std::invalid_argument;
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v6>("0"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v6>("fe80::4a::"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v6>("fe80::4amm::"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v6>("4abd:ee8:f318:9528"), inv_arg);
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v6>("fe80::34abd:ee8:f318:9528"), inv_arg);
    }
  }

}

TEST_CASE("ClientServerBase create_endpoint tests") {
  auto base = ClientServerBase{};

  SECTION("returns endpoint") {

    SECTION("returns endpoint with TCP protocol and unspecified IP address") {
      auto ep = ip::tcp::endpoint{};
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v4>(0));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v4>(3333));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v4>(65535));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v6>(0));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v6>(3333));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v6>(65535));
    }

    SECTION("returns endpoint with UDP protocol and unspecified IP address") {
      auto ep = ip::udp::endpoint{};
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v4>(0));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v4>(3333));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v4>(65535));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v6>(0));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v6>(3333));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v6>(65535));
    }

    SECTION("returns endpoint with TCP protocol and specified IP address") {
      auto ep = ip::tcp::endpoint{};
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v4>(0, ""));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v4>(3333, "0.0.0.1"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v4>(65535, "127.0.0.1"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v6>(0, "::"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v6>(3333, "fe80::4abd:ee8:f318:9528"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::tcp, ip::address_v6>(65535, "fe30::4ab1:ee7:f318:9528"));
    }

    SECTION("returns endpoint with UDP protocol and specified IP address") {
      auto ep = ip::udp::endpoint{};
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v4>(0, ""));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v4>(3333, "0.0.0.1"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v4>(65535, "127.0.0.1"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v6>(0, "::"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v6>(3333, "fe80::4abd:ee8:f318:9528"));
      REQUIRE_NOTHROW(ep = base.create_endpoint<ip::udp, ip::address_v6>(65535, "fe30::4ab1:ee7:f318:9528"));
    }
  }

  SECTION("throw if called with invalid parameters") {
    using inv_args = std::invalid_argument;

    SECTION("throw if protocol TCP and IP can not be parsed") {
      REQUIRE_THROWS_AS(
        (base.create_endpoint<ip::tcp, ip::address_v4>(3333, "127.0.0")), inv_args);
      REQUIRE_THROWS_AS(
        (base.create_endpoint<ip::tcp, ip::address_v6>(3333, "fe80::4abd:")), inv_args);
    }

    SECTION("throw if protocol UDP and IP can not be parsed") {
      REQUIRE_THROWS_AS(
        (base.create_endpoint<ip::udp, ip::address_v4>(3333, "127.00.0.3")), inv_args);
      REQUIRE_THROWS_AS(
        (base.create_endpoint<ip::udp, ip::address_v6>(3333, "fe80::4abd:")), inv_args);
    }
  }

}