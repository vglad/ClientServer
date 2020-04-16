#include "Client.hpp"

#include <iostream>

using namespace clientServer::client;
using namespace boost;

//int Client::create_endpoint() {
//  std::string raw_ip_address = "127.0.0.1";
//  unsigned short port_num = 3333;
//  boost::system::error_code ec;
//  asio::ip::address ip_address =
//                  asio::ip::address::from_string(raw_ip_address, ec);
//  if (ec.value() != 0) {
//    std::cout
//        << "Failed to parse the IP address. Error code = "
//        << ec.value() << ". Message: " << ec.message();
//    return ec.value();
//  }
//  asio::ip::tcp::endpoint ep(ip_address, port_num);
//  return 0;
//}