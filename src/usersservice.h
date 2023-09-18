#ifndef USERSSERVICE_H
#define USERSSERVICE_H

#include "easy_import.h"
#include "itokenvalueprovider.h"
#include "restapi.h"

#include "getallusers.h"
#include "getuserdetails.h"

class UsersService {
    shared_ptr<RestApi> restApi;
    shared_ptr<ITokenValueProvider> tokenValueProvider;
public:
    UsersService(shared_ptr<RestApi> restApi, shared_ptr<ITokenValueProvider> tokenValueProvider)
        : restApi { restApi }
        , tokenValueProvider { tokenValueProvider }
    { qDebug(); };
    ~UsersService() { qDebug(); }

    auto * getUsers(){
        return restApi->execute<GetAllUsersResponse>(
            GetAllUsersRequest(),
            tokenValueProvider->tokenValue()
        );
    };

    auto * getUserDetails(QString const & userId){
        return restApi->execute<GetUserDetailsResponse>(
            GetUserDetailsRequest(userId),
            tokenValueProvider->tokenValue()
        );
    };
};

#endif // USERSSERVICE_H
