#ifndef IHOMEDIPROVIDER_H
#define IHOMEDIPROVIDER_H

#include "easy_import.h"

#include "ilogouttokenprovider.h"
#include "restapi.h"

#include "usersservice.h"
#include "todosservice.h"
#include "profileservice.h"

struct IHomeDiProvider {
    // provide
    unique_ptr<UsersService> usersServiceInstance()
        { return make_unique<UsersService>(restApi(), token()); }

    unique_ptr<ToDosService> todosServiceInstance()
        { return make_unique<ToDosService>(restApi(), token()); }

    unique_ptr<ProfileService> profileServiceInstance()
        { return make_unique<ProfileService>(restApi(), token()); }

    // require
    virtual shared_ptr<ILogoutTokenProvider> logoutTokenProvider() = 0;
protected:
    virtual shared_ptr<RestApi> restApi() = 0;
    virtual QString token() = 0;
};

#endif // IHOMEDIPROVIDER_H
