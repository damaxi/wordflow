#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../include/catch.hpp"
#include "../../lib/src/connection.h"


TEST_CASE( "[GET] Main http curl Connection", "[connection]"){
    restclient::Connection connection;
    restclient::RestResponse res = connection.get("http://httpbin.org/get");
    //std::cout << res.body <<std::endl;
    REQUIRE( res.code == 200);
    REQUIRE( res.body.length() > 0);
}
