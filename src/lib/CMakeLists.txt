cmake_minimum_required(VERSION 3.17)
project(libClientServer)

# Check Boost dependency
include(AddBoostAsio)

find_package(Threads REQUIRED)

set(source_files
    ../../include/lib/ClientServerBase.hpp
    ../../include/lib/Server.hpp
    ../../include/lib/Client.hpp
    ClientServerBase.cpp Server.cpp Client.cpp)
add_library(libClientServer STATIC ${source_files})

target_link_libraries(libClientServer PRIVATE Threads::Threads)
target_include_directories(libClientServer PRIVATE
    ../../ext
    ../../include/detail
    ../../include/lib
)
<<<<<<< HEAD
=======

# Needed definitions for Boost::Asio
set(compile_definitions -DBOOST_ASIO_STANDALONE)
if(WIN32)
  set(compile_definitions -D_WIN32_WINNT=0x0A00 ${compile_definitions})
endif()
>>>>>>> develop
target_compile_definitions(libClientServer PRIVATE ${compile_definitions})
