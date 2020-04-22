cmake_minimum_required (VERSION 3.17)
project(Main)

set(source_files main.cpp)

add_executable(main ${source_files})

target_link_libraries(main PRIVATE libClientServer)
target_include_directories(main PRIVATE
    ../ext
    ../include/detail
    ../include/lib
)

# Needed definitions for Boost::Asio
set(compile_definitions -DBOOST_ASIO_STANDALONE)
if(WIN32)
  set(compile_definitions -D_WIN32_WINNT=0x0A00 ${compile_definitions})
endif()
target_compile_definitions(main PRIVATE ${compile_definitions})
