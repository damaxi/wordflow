//
// Created by martin on 3/2/17.
//

#include <iostream>
#include "connection.h"

 // HELPER funcstions
static size_t write_callback(void *data, size_t size, size_t nmemb, void *userdata);

restclient::Connection::Connection() {
    this->curlHandle = curl_easy_init();
}

restclient::RestResponse restclient::Connection::get(const std::string &url) {
    return perform(url);
}

restclient::RestResponse restclient::Connection::perform(const std::string &url) {
    // init return type
    RestResponse ret = {};

    //std::string url = std::string(this->baseUrl + uri);
    std::string headerString;
    CURLcode res = CURLE_OK;
    curl_slist* headerList = NULL;

    curl_easy_setopt(this->curlHandle, CURLOPT_URL, url.c_str());

    curl_easy_setopt(this->curlHandle, CURLOPT_WRITEFUNCTION,write_callback);
    curl_easy_setopt(this->curlHandle, CURLOPT_WRITEDATA, &ret);

    res = curl_easy_perform(this->curlHandle);

    if (res != CURLE_OK) {
        switch (res) {
            case CURLE_OPERATION_TIMEDOUT:
                ret.code = res;
                ret.body = "Operation Timeout.";
                break;
            case CURLE_SSL_CERTPROBLEM:
                ret.code = res;
                ret.body = curl_easy_strerror(res);
                break;
            default:
                ret.body = "Failed to query.";
                ret.code = -1;
        }
    } else {
        int64_t http_code = 0;
        curl_easy_getinfo(this->curlHandle, CURLINFO_RESPONSE_CODE, &http_code);
        ret.code = static_cast<int>(http_code);
    }

    curl_slist_free_all(headerList);
    curl_easy_reset(this->curlHandle);

    return ret;
}


static size_t write_callback(void *data, size_t size,
                                           size_t nmemb, void *userdata) {
    restclient::RestResponse *r;
    r = static_cast<restclient::RestResponse *>(userdata);
    r->body.append(reinterpret_cast<char *>(data), size * nmemb);
    return (size * nmemb);
}
