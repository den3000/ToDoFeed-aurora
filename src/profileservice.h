#ifndef PROFILESERVICE_H
#define PROFILESERVICE_H

#include "easy_import.h"
#include "restapi.h"

class ProfileService {
    shared_ptr<RestApi> restApi;
    QString token;
public:
    explicit ProfileService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    { qDebug(); };
    ~ProfileService() { qDebug(); };

    void editProfile(){

    };

    void eraseAll(){

    };

    void logout(){

    };
};

#endif // PROFILESERVICE_H
