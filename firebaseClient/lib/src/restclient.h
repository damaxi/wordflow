//
// Created by martin on 3/1/17.
//

#ifndef FIREBASECLIENT_RESTCLIENT_H
#define FIREBASECLIENT_RESTCLIENT_H

#include <string>

namespace  restclient{
    typedef struct {
        int code;
        std::string body;
    } RestResponse;

    class RestClient {

    public:
        RestClient();

        RestResponse get(const std::string& url);
    };
}


#endif //FIREBASECLIENT_RESTCLIENT_H
