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
    auto cli = Client{};
    auto srv = Server{};

    cli.create_endpoint<ip::tcp, ip::address_v4>(3333, "127.0.0.1");
  }
  catch (std::exception const &) {
     print_nested_exception();
  }
  return 0;
}
