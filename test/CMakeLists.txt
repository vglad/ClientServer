cmake_minimum_required (VERSION 3.17)
project(tests LANGUAGES CXX)

option(SKIP_CATCH2_DOWNLOAD "Do not download Catch2" OFF)
option(SKIP_TROMPELOEIL_DOWNLOAD "Do not download Trompeloeil" OFF)

include(AddCatch2)
include(AddTrompeloeil)

set(source_files
    catch_main.cpp 
    ClientServerBaseTests.cpp
    ServerTests.cpp
    ClientTests.cpp
    )

add_executable(tests ${source_files})
target_link_libraries(tests PRIVATE ${catch2} ${trompeloeil} libClientServer)
target_include_directories(tests PRIVATE
    ../ext
    ../include/detail
    ../include/lib
)

set(compile_definitions -DBOOST_ASIO_STANDALONE)
if(WIN32)
  # Needed definition for Boost::Asio
  set(compile_definitions -D_WIN32_WINNT=0x0A00 ${compile_definitions})
endif()
target_compile_definitions(tests PRIVATE ${compile_definitions})

# Disable warning in Clang 10 and GCC 9
# Fixed in next Trompeloeil beta release
if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
  target_compile_options(tests PRIVATE -Wno-deprecated-declarations)
endif ()
