#ifndef IHOMEDIPROVIDER_H
#define IHOMEDIPROVIDER_H

#include "easy_import.h"
#include "usersservice.h"
#include "todosservice.h"
#include "profileservice.h"

struct IHomeDiProvider {
    unique_ptr<UsersService> usersServiceInstance(shared_ptr<RestApi> restApi, QString const & token) {
        return make_unique<UsersService>(restApi, token);
    }

    unique_ptr<ToDosService> todosServiceInstance(shared_ptr<RestApi> restApi, QString const & token) {
        return make_unique<ToDosService>(restApi, token);
    }

    unique_ptr<ProfileService> profileServiceInstance(shared_ptr<RestApi> restApi, QString const & token) {
        return make_unique<ProfileService>(restApi, token);
    }
};

#endif // IHOMEDIPROVIDER_H
