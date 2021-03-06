#include "Precompiled.hpp"
#include "Client.hpp"
#include "Server.hpp"

using namespace clientServer;
using namespace clientServer::client;
using namespace clientServer::server;
using namespace clientServer::detail;
using namespace boost::asio;

int main() {
  try {
    auto srv = Server{};
    auto srv_ep = srv.create_endpoint<ip::udp, ip::address_v4>(5555);
    std::cout << srv_ep.address() << ":" << srv_ep.port() << '\n';

    auto cli = Client{};
    auto cli_ep = cli.create_endpoint<ip::tcp, ip::address_v4>(3333, "127.0.0.1");
    std::cout << cli_ep.address() << ":" << cli_ep.port() << '\n';
  }
  catch (std::exception const & e) {
     print_nested_exception(e);
  }
  return 0;
}
