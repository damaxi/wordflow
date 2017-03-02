cmake_minimum_required(VERSION 3.6)
project(testlib)

set(CMAKE_CXX_STANDARD 11)
FIND_PACKAGE(CURL)
IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

set(SOURCE_FILES src/tests.cpp)
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests firebaseClient ${requiredlibs})

