#ifndef ISTARTDIPROVIDER_H
#define ISTARTDIPROVIDER_H

#include "easy_import.h"
#include "startservice.h"

struct IStartDiProvider {
    unique_ptr<StartService> startServiceInstance(shared_ptr<RestApi> restApi) {
        return make_unique<StartService>(restApi);
    }
};

#endif // ISTARTDIPROVIDER_H
