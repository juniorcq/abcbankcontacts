#
# CMakeLists.txt
#
#

# Minimum version of CMake
cmake_minimum_required(VERSION 3.15)

# Name for this CMake project
project(abcbankcontacts)

#
set(sources sqlite3.h sqlite3.c crow_all.h
Address.h
Address.cpp
Contact.h
Contact.cpp
DBConnection.h
DBConnection.cpp
DBController.h
DBController.cpp
Phone.h
Phone.cpp
abcbankcontacts.cpp)

#
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.db ${CMAKE_CURRENT_BINARY_DIR}/example.db COPYONLY)

#
add_executable(abcbankcontacts ${sources})
target_include_directories(abcbankcontacts BEFORE PUBLIC "boost_1_79_0")
