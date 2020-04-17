#ifndef CLIENTSERVER_INCLUDE_DETAIL_STRINGUTILS_HPP
#define CLIENTSERVER_INCLUDE_DETAIL_STRINGUTILS_HPP

#include <iostream>
#include <sstream>

namespace clientServer::detail {

  //*****************************************************************************
  // Text concatenation

  template<typename T>
  static std::string concat(const T & value) {
    std::ostringstream tmp_str;
    tmp_str << value;
    return tmp_str.str();
  }

  template<typename T, typename ... Args>
  static std::string concat(const T & value, const Args & ... args) {
    return concat(value) + concat(args...);
  }
  //*****************************************************************************

  //*****************************************************************************
  // Check that part of IPv4 address is between 0 and 255
  [[maybe_unused]] static inline void check_ip_part(std::string const & ip_part) {
    try {
      if (ip_part.empty()) {
        throw std::invalid_argument("Part of IP is empty");
      }
      auto result = stoull(ip_part);
      if ( (result < std::numeric_limits<uint8_t>::min())
           || (result > std::numeric_limits<uint8_t>::max()))
      {
        throw std::out_of_range("Part of IP is out of range");
      }
    }
    catch (...) {
      std::throw_with_nested(std::runtime_error("IP check failed"));
    }
  }
  //*****************************************************************************

}

#endif //CLIENTSERVER_INCLUDE_DETAIL_STRINGUTILS_HPP