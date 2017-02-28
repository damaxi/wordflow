cmake_minimum_required(VERSION 3.6)
project(testlib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/tests.cpp)
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests firebaseClient)

