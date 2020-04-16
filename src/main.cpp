//#include "Precompiled.hpp"
//#include "Client.hpp"
//#include "Server.hpp"

#include <boost/asio.hpp>
#include <iostream>

//using namespace clientServer;
//using namespace clientServer::client;
//using namespace clientServer::server;
//using namespace clientServer::detail;
using namespace boost::asio;

int main() {
  try {
    //auto cli = Client{};
    //cli.create_endpoint<ip::tcp, ip::address_v4>(3333, "127");
    auto ec         = boost::system::error_code{};
    auto ip = ip::address_v4::from_string("127.00.0", ec);
    std::cout << ip << "\n" << ec.message();
  }
  catch (std::exception const & ex) {
    std::cout << "std::exception:" << ex.what() << std::endl;
     //print_nested_exception();
  }
  return 0;
}
