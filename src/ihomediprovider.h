#ifndef IHOMEDIPROVIDER_H
#define IHOMEDIPROVIDER_H

#include "easy_import.h"

struct IHomeDiProvider {
    unique_ptr<QString> someHome() {
        return make_unique<QString>("start");
    };
};

#endif // IHOMEDIPROVIDER_H
