//
// Created by martin on 3/2/17.
//

#ifndef FIREBASECLIENT_CONNECTION_H
#define FIREBASECLIENT_CONNECTION_H

#include <string>
#include "restclient.h"
#include <curl/curl.h>

namespace restclient {

    class Connection {

    private:
        CURL *curlHandle;
        RestResponse perform(const std::string& url);

    public:

        explicit Connection();

        RestResponse get(const std::string& url);
    };
}


#endif //FIREBASECLIENT_CONNECTION_H
