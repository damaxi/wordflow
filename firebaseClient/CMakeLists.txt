cmake_minimum_required(VERSION 3.6)
project(firebaseClient)

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_C_FLAGS_DEBUG   "-O2 -Wall -ggdb" )
set( CMAKE_CXX_FLAGS_DEBUG "-O2 -Wall -ggdb" )

add_subdirectory(lib)
add_subdirectory(tests)

