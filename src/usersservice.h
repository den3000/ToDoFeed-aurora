#ifndef USERSSERVICE_H
#define USERSSERVICE_H

#include "easy_import.h"
#include "restapi.h"

#include "getallusers.h"
#include "getuserdetails.h"

class UsersService {
    shared_ptr<RestApi> restApi;
    QString token;
public:
    UsersService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    { qDebug(); };
    ~UsersService() { qDebug(); }

    auto * getUsers(){
        return restApi->execute<GetAllUsersResponse>(
            GetAllUsersRequest(),
            token
        );
    };

    auto * getUserDetails(QString const & userId){
        return restApi->execute<GetUserDetailsResponse>(
            GetUserDetailsRequest(userId),
            token
        );
    };
};

#endif // USERSSERVICE_H
