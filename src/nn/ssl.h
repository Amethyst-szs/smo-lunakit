#pragma once

#include <nn/result.h>

namespace nn::ssl {

    enum CertificateFormat {};

    class Context {
    public:

        enum SslVersion {
            UNK1,
            UNK2
        };

        nn::Result Create(SslVersion ver);
        void ImportServerPki(ulong *,char const*,uint,nn::ssl::CertificateFormat);
    };

    void Initialize();
    void Finalize();
}