#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "ClientServerBase.hpp"

using namespace clientServer;
using namespace boost::asio;

TEST_CASE("ClientServerBase get_ip tests") {
  auto base = ClientServerBase{};

  SECTION("returns proper IP type") {

    SECTION("returns proper IP type if IPv4 and properly parsed") {
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

    SECTION("returns proper IP type if IPv6 and properly parsed") {
      auto ip = ip::address_v6{};
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v6>(""));
      REQUIRE(ip.any() == ip::address_v6());
      REQUIRE_NOTHROW(ip = base.get_ip<ip::address_v6>("fe80::4abd:ee8:f318:9528"));
      REQUIRE(ip.any() == ip::address_v6());
    }

  }

  SECTION("throw if invalid ip address format") {

    SECTION("throw if protocol IPv4 and not parsed") {
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

    SECTION("throw if protocol IPv6 and not parsed") {
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

  SECTION("returns endpoint if parameters valid") {
    SECTION("returns endpoint with specified port number, "
            "TCP protocol and IP address v4, unspecified") {
      auto ep = base.create_endpoint<ip::tcp, ip::address_v4>(3333);
      REQUIRE(ep.port() == 3333);
      REQUIRE(ep.address().is_v4());
      REQUIRE(ep.protocol().protocol() == ip::tcp::v4().protocol());
    }
//
//    SECTION("returns endpoint with specified port number, "
//            "TCP protocol and IP address v4, 127.0.0.1") {
//      auto ep = base.create_endpoint<ip::tcp, ip::address_v4>(
//          3333, "127.0.0.1");
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v4());
//      REQUIRE(ep.address().to_string() == "127.0.0.1");
//      REQUIRE(ep.protocol().protocol() == ip::tcp::v4().protocol());
//    }
//
//    SECTION("returns endpoint with specified port number, "
//            "TCP protocol and IP address v6, unspecified") {
//      auto ep = base.create_endpoint<ip::tcp, ip::address_v6>(3333);
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v6());
//      REQUIRE(ep.protocol().protocol() == ip::tcp::v6().protocol());
//    }
//
//    SECTION("returns endpoint with specified port number, "
//            "TCP protocol and IP address v6, fe80::4abd:ee8:f318:9528") {
//      auto ep = base.create_endpoint<ip::tcp, ip::address_v6>(
//          3333, "fe80::4abd:ee8:f318:9528");
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v6());
//      REQUIRE(ep.address().to_string() == "fe80::4abd:ee8:f318:9528");
//      REQUIRE(ep.protocol().protocol() == ip::tcp::v6().protocol());
//    }
//
//    SECTION("returns endpoint with specified port number, "
//            "UDP protocol and IP address v4, unspecified") {
//      auto ep = base.create_endpoint<ip::udp, ip::address_v4>(3333);
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v4());
//      REQUIRE(ep.protocol().protocol() == ip::udp::v4().protocol());
//    }
//
//    SECTION("returns endpoint with specified port number, "
//            "UDP protocol and IP address v4, 127.0.0.1") {
//      auto ep = base.create_endpoint<ip::udp, ip::address_v4>(
//          3333, "127.0.0.1");
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v4());
//      REQUIRE(ep.address().to_string() == "127.0.0.1");
//      REQUIRE(ep.protocol().protocol() == ip::udp::v4().protocol());
//    }
//
//    SECTION("returns endpoint with specified port number, "
//            "UDP protocol and IP address v6, unspecified") {
//      auto ep = base.create_endpoint<ip::udp, ip::address_v6>(3333);
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v6());
//      REQUIRE(ep.protocol().protocol() == ip::udp::v6().protocol());
//    }
//
//    SECTION("returns endpoint with specified port number, "
//            "UDP protocol and IP address v6, fe80::4abd:ee8:f318:9528") {
//      auto ep = base.create_endpoint<ip::udp, ip::address_v6>(
//          3333, "fe80::4abd:ee8:f318:9528");
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v6());
//      REQUIRE(ep.address().to_string() == "fe80::4abd:ee8:f318:9528");
//      REQUIRE(ep.protocol().protocol() == ip::udp::v6().protocol());
//    }
  }
}