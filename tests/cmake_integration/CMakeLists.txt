cmake_minimum_required(VERSION 3.3)

include(ExternalProject)

# From https://stackoverflow.com/a/48555098/9189546
get_cmake_property(vars CACHE_VARIABLES)
foreach(var ${vars})
  get_property(currentHelpString CACHE "${var}" PROPERTY HELPSTRING)
    if("${currentHelpString}" MATCHES "No help, variable specified on the command line." OR "${currentHelpString}" STREQUAL "")
        # message("${var} = [${${var}}]  --  ${currentHelpString}") # uncomment to see the variables being processed
        list(APPEND CL_ARGS "-D${var}=${${var}}")
    endif()
endforeach()

project(opendds_cmake_tests)

ExternalProject_Add(opendds_cmake_messenger_1
  SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/Messenger/Messenger_1"
  CMAKE_ARGS ${CL_ARGS}
)

add_custom_target(opendds_cmake_tests
    DEPENDS
      opendds_cmake_messenger_1
)
