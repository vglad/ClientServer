#include "Precompiled.hpp"
#include "Client.hpp"
#include "Server.hpp"

#include <exception>

using namespace clientServer;
using namespace clientServer::client;
using namespace clientServer::server;
using namespace clientServer::detail;
using namespace boost::asio;

int main() {
  try {
    auto cli = Client{};
    auto ep = cli.create_endpoint<ip::tcp, ip::address_v4>(3333, "128.6.65.2");

    std::cout << concat(std::string("1"), "2", ep.port());
  }
  catch (std::exception const &) {
     print_nested_exception();
  }
  return 0;
}
