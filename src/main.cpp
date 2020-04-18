#include "Precompiled.hpp"
#include "Client.hpp"
#include "Server.hpp"

#include <iostream>
#include <exception>
#include <algorithm>

using namespace clientServer;
using namespace clientServer::client;
using namespace clientServer::server;
using namespace clientServer::detail;
using namespace boost::asio;



bool check_ip(std::string const & raw_ip) {
  if (raw_ip.size() < 7 || raw_ip.size() > 15
      || raw_ip.find_first_not_of("1234567890.") != std::string::npos
      || std::count(raw_ip.begin(), raw_ip.end(), '.') != 3) {
    std::throw_with_nested(std::invalid_argument("Wrong IP address format"));
  }

  size_t begin_pos = 0;
  for (size_t i = 0; i < 3; i++) {
    auto ip_part = raw_ip.substr(begin_pos,
                                 raw_ip.find_first_of('.', begin_pos));
    begin_pos += ip_part.size() + 1;
    check_ip_part(ip_part);
  }

  auto ip_part = raw_ip.substr(begin_pos, raw_ip.size());
  check_ip_part(ip_part);

  return true;
}

int main() {
  try {
    auto cli = Client{};
    cli.create_endpoint<ip::tcp, ip::address_v4>(3333, "128.6.65.2");

//    auto ec = boost::system::error_code{};
//    auto ip = std::string {"13..99.2"};
//    check_ip(ip);
//
//    if (ec) {
//      std::ostringstream msg;
//      msg << ip << "\n" << "value [" << ec.value() << "]\n"
//                << "message [" << ec.message() << "]";
//      throw (std::invalid_argument(msg.str()));
//    } else {
//      std::cout << ip;
//    }
  }
  catch (std::exception const &) {
     print_nested_exception();
  }
  return 0;
}
