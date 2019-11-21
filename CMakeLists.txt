cmake_minimum_required (VERSION 3.10)

project (cpp_property)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(cpp_property INTERFACE)
target_include_directories(cpp_property INTERFACE ./include/)
set(cpp_property_include ${CMAKE_CURRENT_LIST_DIR}/include/)
set(cpp_property_include ${cpp_property_include} PARENT_SCOPE)
