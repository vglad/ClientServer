#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "ClientServerBase.hpp"
#include "StringUtils.hpp"

using namespace clientServer;
using namespace boost::asio;

TEST_CASE("testing get_ip") {
  auto base = ClientServerBase{};

  SECTION("returns proper IP type") {
    SECTION("returns proper IP type if IPv4 and properly parsed") {
      auto ip = base.get_ip<ip::address_v4>("127.0.0.1");
      REQUIRE(ip.to_string() == "127.0.0.1");
      REQUIRE(ip.any() == ip::address_v4());
    }

    SECTION("returns proper IP type if IPv6 and properly parsed") {
      auto ip = base.get_ip<ip::address_v6>("fe80::4abd:ee8:f318:9528");
      REQUIRE(ip.to_string() == "fe80::4abd:ee8:f318:9528");
      REQUIRE(ip.any() == ip::address_v6());
    }

  }

  SECTION("returns error if parameters invalid") {
    auto errNum = 22;
#ifdef WIN32
    errNum = 10022;
#endif

    SECTION("throw if protocol IPv4 and not parsed") {
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v4>("127.0.0"),
                        std::invalid_argument);
      REQUIRE_THROWS_WITH(
          base.get_ip<ip::address_v4>("127.0.0"),
          Catch::Contains(concat("Failed to parse IP address: [IPv4, 127.0.0]. ",
                                 "Error #: ", errNum))
      );
    }

    SECTION("throw if protocol IPv6 and not parsed") {
      REQUIRE_THROWS_AS(base.get_ip<ip::address_v6>("fe80::4a::"),
                        std::invalid_argument);
      REQUIRE_THROWS_WITH(
          base.get_ip<ip::address_v6>("fe80::4a::"),
          Catch::Contains(concat("Failed to parse IP address: [IPv6, fe80::4a::]. ",
                                 "Error #: ", errNum))
      );
    }
  }
}

//TEST_CASE("ClientServerBase create_endpoint", "[ClientServerBase]") {
//  auto base = ClientServerBase{};
//
//  SECTION("returns endpoint if parameters valid") {
//    SECTION("returns endpoint with specified port number, "
//            "TCP protocol and IP address v4, unspecified") {
//      auto ep = base.create_endpoint<ip::tcp, ip::address_v4>(3333);
//      REQUIRE(ep.port() == 3333);
//      REQUIRE(ep.address().is_v4());
//      REQUIRE(ep.protocol().protocol() == ip::tcp::v4().protocol());
//    }
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
//  }
//}