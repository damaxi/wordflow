cmake_minimum_required(VERSION 3.6)
project(mainlib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES include/firebaseclient.h src/firebaseclient.cpp)
add_library(firebaseClient SHARED ${SOURCE_FILES})