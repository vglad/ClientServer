#ifndef CLIENTSERVER_INCLUDE_LIB_CLIENTSERVERBASE_HPP
#define CLIENTSERVER_INCLUDE_LIB_CLIENTSERVERBASE_HPP

#include "StringUtils.hpp"

#include <string>
#include <boost/asio.hpp>

namespace clientServer {

  using namespace clientServer::detail;
  using namespace boost::asio;


  class ClientServerBase {
  public:

    template <typename Protocol, typename IPAddrVersion>
    typename Protocol::endpoint
    create_endpoint(uint16_t port_num, std::string const & raw_ip = std::string{}) {
      try {
        auto ip_address = get_ip<IPAddrVersion>(raw_ip);
        return typename Protocol::endpoint(ip_address, port_num);
      }
      catch (...) {
        std::throw_with_nested(std::invalid_argument("Failed to create endpoint"));
      }
    }

    template <typename IPAddrVersion>
    IPAddrVersion get_ip(std::string const & raw_ip) const {
      if (raw_ip.empty()) { return IPAddrVersion::any(); }

      auto ec                  = boost::system::error_code{};
      auto ip_addr             = IPAddrVersion::from_string(raw_ip, ec);
      auto raw_ip_from_ip_addr = ip_addr.to_string();

      auto err_msg             = std::ostringstream{};
      err_msg << "Failed to parse IP address: ["
              << (std::is_same_v<IPAddrVersion, ip::address_v4> ? "IPv4" : "IPv6")
              << ", " << raw_ip << "]\n";

      if (ec.value() != 0) {
        err_msg << "Error #: [" << ec.value() << "]: " << ec.message();
        std::throw_with_nested(std::invalid_argument(err_msg.str()));
      }
      if (raw_ip_from_ip_addr != raw_ip) {
        std::throw_with_nested(std::invalid_argument(err_msg.str()));
      }
      return ip_addr;
    }

  };

}
#endif //CLIENTSERVER_INCLUDE_LIB_CLIENTSERVERBASE_HPP