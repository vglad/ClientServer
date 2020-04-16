message(STATUS "Checking Boost::Asio dependency ...")

# Delete "ext/boost" directory to download all needed Boost::Asio dependencies

if (NOT EXISTS ${BOOST_DIR})
  message(STATUS "  Boost::Asio not found")
  message(STATUS "  Downloading Boost::Asio ...")

  set(boost_major_ver    "1")
  set(boost_minor_ver    "72")
  set(boost_revision_ver "0")
  set(boost_ver "${boost_major_ver}.${boost_minor_ver}.${boost_revision_ver}")
  set(boost_temp_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/boost_tar_temp)
  set(boost_components asio system config winapi predef)

  foreach (component IN LISTS boost_components)
    set(component_tar ${boost_temp_dir}/${component}-boost-${boost_ver}.tar.gz)

    # Download only needed components for Boost::Asio
    if (NOT EXISTS ${component_tar})
      message(STATUS "    Downloading ${component} ...")
      set(url https://codeload.github.com/boostorg/${component}/tar.gz/boost-${boost_ver})
      file(DOWNLOAD ${url} ${component_tar}
          INACTIVITY_TIMEOUT 10 STATUS status LOG log)
      list(GET status 0 status_code)
      list(GET status 1 status_string)
      if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "ERROR: downloading '${url}' failed
          status_code: ${status_code}
          status_string: ${status_string}
          log: ${log}"
        )
      endif()
    endif ()

    message(STATUS "    Extracting ${component}-boost-${boost_ver}.tar.gz ...")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xzf ${component_tar} ${component}-boost-${boost_ver}/include
      WORKING_DIRECTORY ${boost_temp_dir}
    )
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${boost_temp_dir}/../boost
      WORKING_DIRECTORY ${boost_temp_dir}
    )
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${component}-boost-${boost_ver}/include/boost ${boost_temp_dir}/../boost
      WORKING_DIRECTORY ${boost_temp_dir}
    )
    execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf ${boost_temp_dir}
      WORKING_DIRECTORY ${boost_temp_dir}/..
    )
  endforeach ()

endif()
message(STATUS "Boost::Asio dependency prepared")