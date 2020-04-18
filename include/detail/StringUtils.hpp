#ifndef CLIENTSERVER_INCLUDE_DETAIL_STRINGUTILS_HPP
#define CLIENTSERVER_INCLUDE_DETAIL_STRINGUTILS_HPP

#include <sstream>

namespace clientServer::detail {

  template<typename... T>
  static std::string concat (T const & ... args) {
    std::ostringstream os{};
    (os << ... << args);
    return os.str();
  }

}

#endif //CLIENTSERVER_INCLUDE_DETAIL_STRINGUTILS_HPP