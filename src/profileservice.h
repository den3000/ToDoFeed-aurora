#ifndef PROFILESERVICE_H
#define PROFILESERVICE_H

#include "easy_import.h"
#include "restapi.h"

#include "getprofile.h"
#include "eraseall.h"
#include "editprofile.h"

class ProfileService {
    shared_ptr<RestApi> restApi;
    QString token;
public:
    explicit ProfileService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    { qDebug(); }
    ~ProfileService() { qDebug(); }

    auto * getProfile() {
        return restApi->execute<GetProfileResponse>(
            GetProfileRequest(),
            token
        );
    }

    auto * updateProfile(QString const & firstName,
                         QString const & lastName,
                         QString const & about
    ) {
        return restApi->execute<EditProfileResponse>(
            EditProfileRequest(firstName, lastName, about),
            token
        );
    }

    auto * eraseAll() {
        return restApi->execute<EraseAllResponse>(
            EraseAllRequest(),
            token
        );
    }
};

#endif // PROFILESERVICE_H
