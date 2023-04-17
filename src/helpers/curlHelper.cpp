#include <helpers/curlHelper.h>
#include <nn/ssl.h>

namespace curlHelper {
    int DataDownloader::CreateSslCtx(CURL* curl, void* ssl_ctx, void* clientp) {
        auto *ctx = (nn::ssl::Context*)ssl_ctx;
        if(ctx->Create(nn::ssl::Context::SslVersion::UNK2).isSuccess()) {
            return CURLE_OK;
        }
        return -1;
    }

    size_t DataDownloader::DataWrite(char* ptr, size_t size, size_t nmemb, void* userdata) {
        auto *curlData = (DataStream*)userdata;
        size_t dataSize = size * nmemb;
        return curlData->write(ptr, dataSize);
    }

    void DataDownloader::downloadFromUrl(DataStream& data, const char* url) {

        CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

        if(result != CURLcode::CURLE_OK) {
            Logger::log("init returned non ok! Val: %d\n", curl_easy_strerror(result));
            return;
        }

        CURL* curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, CURLPROTO_ALL);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DataDownloader::DataWrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&data);
        curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, DataDownloader::CreateSslCtx);

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
            Logger::log("curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

        Logger::log("Downloaded Data Size: %d\n", data.getSize());

        curl_easy_cleanup(curl);
    }
}