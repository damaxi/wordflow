//
// Created by martin on 3/2/17.
//

#ifndef FIREBASECLIENT_CONNECTION_H
#define FIREBASECLIENT_CONNECTION_H

#include <string>
#include <map>
#include "restclient.h"
#include <curl/curl.h>

namespace restclient {

    typedef std::map<std::string,std::string> headers_t;

    class Connection {

    private:
        CURL *curlHandle;
        headers_t headers;
        RestResponse perform(const std::string& url);

    public:
        std::string headersToString() const;

    public:

        explicit Connection();

        RestResponse get(const std::string& url);

        restclient::Connection & addHeader(std::string &key, std::string &value);

        restclient::Connection & addHeader(std::string key, std::string value);

    };
}


#endif //FIREBASECLIENT_CONNECTION_H
