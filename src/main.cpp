#include "Precompiled.hpp"
#include "Client.hpp"
#include "Server.hpp"

#include <iostream>

using namespace clientServer;
using namespace clientServer::client;
using namespace clientServer::server;
using namespace clientServer::detail;
using namespace boost::asio;

int main() {
  try {
//    auto cli = Client{};
//    cli.create_endpoint<ip::tcp, ip::address_v4>(3333, "127.0.0.1");
    auto ec = boost::system::error_code{};
    auto ip = ip::address_v4::from_string("127.0.0", ec);
    if (ec) {
      std::ostringstream msg;
      msg << ip << "\n" << "value [" << ec.value() << "]\n"
                << "message [" << ec.message() << "]";
      throw (std::invalid_argument(msg.str()));
    } else {
      std::cout << ip;
    }
  }
  catch (std::exception const &) {
     print_nested_exception();
  }
  return 0;
}
