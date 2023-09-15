#ifndef PROFILESERVICE_H
#define PROFILESERVICE_H

#include "easy_import.h"
#include "restapi.h"

class ProfileService {
    shared_ptr<RestApi> restApi;
    QString token;

    ProfileService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    {};

    void editProfile(){

    };

    void eraseAll(){

    };

    void logout(){

    };
};

#endif // PROFILESERVICE_H
