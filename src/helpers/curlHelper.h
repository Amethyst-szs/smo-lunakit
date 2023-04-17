#pragma once

#include <nn/socket.hpp>
#include <curl/curl.h>
#include <helpers/DataStream.h>
#include "types.h"

namespace curlHelper {
    class DataDownloader {

        static int CreateSslCtx(CURL *curl, void *ssl_ctx, void *clientp);

        static size_t DataWrite(char *ptr, size_t size, size_t nmemb, void *userdata);

    public:

        DataDownloader() = default;

        static void downloadFromUrl(DataStream& data, const char* url);
    };
}