project(opendds_devguide_messenger CXX)
cmake_minimum_required(VERSION 3.3)
enable_testing()

find_package(OpenDDS REQUIRED)

add_library(example_idl)
OPENDDS_TARGET_SOURCES(example_idl PUBLIC "Messenger.idl")
target_link_libraries(example_idl PUBLIC TAO::TAO)

add_executable(example example.cpp)
target_link_libraries(example example_idl)
