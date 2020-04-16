cmake_minimum_required(VERSION 3.17)
project(libClientServer)

# Check Boost dependency
include(AddBoostAsio)

find_package(Threads REQUIRED)

set(source_files ClientServerBase.cpp Server.cpp Client.cpp)
add_library(libClientServer STATIC ${source_files})

target_link_libraries(libClientServer PRIVATE Threads::Threads)
target_include_directories(libClientServer PRIVATE
    ../../ext
    ../../include/detail
    ../../include/lib
)

if(WIN32)
  target_compile_definitions(libClientServer
      PRIVATE "-DBOOST_ASIO_STANDALONE -D_WIN32_WINNT=0x0A00")
#      PRIVATE "-DBOOST_ALL_NO_LIB -DBOOST_ASIO_STANDALONE -DBOOST_ERROR_CODE_HEADER_ONLY -D_WIN32_WINNT=0x0A00")
endif()
