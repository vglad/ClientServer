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
    template <typename ProtocolT, typename IPAddrT>
      typename ProtocolT::endpoint
      create_endpoint(int16_t port_num, std::string const & raw_ip = std::string{}) {
        try {
          auto ip_address = get_ip<IPAddrT>(raw_ip);
          return typename ProtocolT::endpoint(ip_address, port_num);
        }
        catch (...) {
          std::throw_with_nested(std::invalid_argument("Failed to create endpoint"));
        }
      }

    template<typename IPAddrT>
      IPAddrT
      get_ip(std::string const & raw_ip) const {
        if (raw_ip.empty()) { return IPAddrT::any(); }
        auto ec         = boost::system::error_code{};
        auto ip_address = IPAddrT::from_string(raw_ip, ec);
        if (ec.value() != 0) {
          std::throw_with_nested(std::invalid_argument(concat(
              "Failed to parse IP address: [",
              std::is_same_v<IPAddrT, ip::address_v4> ? "IPv4" : "IPv6", ", ",
              raw_ip, "]. Error #: ", ec.value(), ". Message: ", ec.message()
          )));
        }
        return ip_address;
      }

  };

}
#endif //CLIENTSERVER_INCLUDE_LIB_CLIENTSERVERBASE_HPP