#ifndef PROFILESERVICE_H
#define PROFILESERVICE_H

#include "easy_import.h"
#include "restapi.h"

#include "getprofile.h"

class ProfileService {
    shared_ptr<RestApi> restApi;
    QString token;
public:
    explicit ProfileService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    { qDebug(); };
    ~ProfileService() { qDebug(); };

    auto * getProfile() {
        return restApi->execute<GetProfileResponse>(
            GetProfileRequest(),
            token
        );
    }

    void updateProfile(){

    };

    void eraseAll(){

    };
};

#endif // PROFILESERVICE_H
