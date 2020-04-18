cmake_minimum_required (VERSION 3.17)
project(ClientServer LANGUAGES CXX)

option(SKIP_TESTS "Do not build unit tests" OFF)
set(BOOST_DIR ${PROJECT_SOURCE_DIR}/ext/boost)

# Setting compile definition for all projects to build Boost::Asio as header only
set(compile_definitions -DBOOST_ASIO_STANDALONE)
if(WIN32)
  set(compile_definitions -D_WIN32_WINNT=0x0A00 ${compile_definitions})
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
add_subdirectory(src/lib)
add_subdirectory(src)

if (NOT SKIP_TESTS)
  add_subdirectory(test)
  set(targets tests)
endif()

set(targets libClientServer main ${targets})
set_target_properties(${targets} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)


