#include "helpers/DataStream.h"
#include "nn/socket.hpp"

#include <heap/seadHeapMgr.h>
#include <curl/curl.h>

size_t test_curl_write(char *ptr, size_t size, size_t nmemb, void *userdata) {
    auto *curlData = (DataStream*)userdata;
    size_t dataSize = size * nmemb;
    Logger::log("Data Size: %i\n", dataSize);
    return curlData->write(ptr, dataSize);
}

namespace nn::ssl {
    class Context {
    public:

        enum SslVersion {
            UNK1,
            UNK2
        };

        bool Create(SslVersion ver);
    };

    void Initialize();
    void Finalize();
}

//int test_curl_ssl(CURL *curl, void *ssl_ctx, void *clientp) {
//    nn::ssl::Context *ctx = (nn::ssl::Context*)ssl_ctx;
//    if(ctx->Create(nn::ssl::Context::SslVersion::UNK2)) {
//        return CURLE_OK;
//    }
//    return -1;
//}

#define WAITMS(x)                               \
  struct timeval wait = { 0, (x) * 1000 };      \
  (void)nn::socket::Select(0, nullptr, nullptr, nullptr, &wait);

// void test_curl(sead::Heap *heap) {
//     sead::ScopedCurrentHeapSetter setter(heap);

//     nn::ssl::Initialize();

//     CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

//     if(result != CURLcode::CURLE_OK) {
//         Logger::log("init returned non ok! Val: %d\n", curl_easy_strerror(result));
//         return;
//     }

//     CURL* curl = curl_easy_init();
//     CURLM* multi = curl_multi_init();

//     DataStream curlData(0x10);

//     if(curl && multi) {
//         curl_easy_setopt(curl, CURLOPT_URL, "url here");
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, test_curl_write);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&curlData);

//         curl_multi_add_handle(multi, curl);

//         result = curl_easy_perform(curl);

//         if(result != CURLE_OK)
//             Logger::log("curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

//         int still_running = 1;
//         int repeats = 0;

//         curl_multi_perform(multi, &still_running);

//         do {
//             int numfds;
//             CURLMcode code = curl_multi_wait(multi, nullptr, 0, 1000, &numfds);

//             if(code != CURLM_OK) {
//                 Logger::log("curl_multi_wait() failed, code %d.\n", code);
//                 break;
//             }

//             if(!numfds) {
//                 repeats++; /* count number of repeated zero numfds */
//                 if(repeats > 1) {
//                     WAITMS(100); /* sleep 100 milliseconds */
//                 }
//             }
//             else
//                 repeats = 0;

//             curl_multi_perform(multi, &still_running);

//         }while(still_running);

//         FsHelper::writeFileToPath(curlData.getData(), curlData.getSize(), "sd:/LunaKit/File.bin");

//         curl_multi_remove_handle(multi, curl);

//         curl_easy_cleanup(curl);

//         curl_multi_cleanup(multi);

//         Logger::log("Curl test successful.\n");

//         return;
//     }

//     Logger::log("Curl test failed!\n");

// }