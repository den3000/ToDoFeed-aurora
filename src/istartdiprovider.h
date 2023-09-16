#ifndef ISTARTDIPROVIDER_H
#define ISTARTDIPROVIDER_H

#include "easy_import.h"

#include "ilogintokenprovider.h"
#include "restapi.h"

#include "startservice.h"

#include "startvm.h"
#include "loginvm.h"
#include "editprofilevm.h"

struct IStartDiProvider {
    // provide
    unique_ptr<StartService> startServiceInstance()
        { return make_unique<StartService>(restApi()); }

    unique_ptr<StartVM> startVmInstance()
        { return make_unique<StartVM>(); }

    unique_ptr<LoginVM> loginVmInstance(shared_ptr<StartService> service)
        { return make_unique<LoginVM>(loginTokenProvider(), service); }

    unique_ptr<EditProfileVM> editProfileInstance(shared_ptr<StartService> service)
        { return make_unique<EditProfileVM>(loginTokenProvider(), service); }

    // require
    virtual shared_ptr<ILoginTokenProvider> loginTokenProvider() = 0;
protected:
    virtual shared_ptr<RestApi> restApi() = 0;
};

#endif // ISTARTDIPROVIDER_H
