cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

include(../CMakeLists.txt)
add_executable(cpp_property_test main.cpp)
target_link_libraries(cpp_property_test cpp_property)
target_include_directories(cpp_property_test PRIVATE ${cpp_property_include})