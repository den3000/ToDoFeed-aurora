#ifndef ISTARTDIPROVIDER_H
#define ISTARTDIPROVIDER_H

#include "easy_import.h"

#include "ilogintokenprovider.h"
#include "restapi.h"

#include "startservice.h"

struct IStartDiProvider {
    // provide
    unique_ptr<StartService> startServiceInstance()
        { return make_unique<StartService>(restApi()); }

    // require
    virtual shared_ptr<ILoginTokenProvider> loginTokenProvider() = 0;
protected:
    virtual shared_ptr<RestApi> restApi() = 0;
};

#endif // ISTARTDIPROVIDER_H
