#ifndef PROFILESERVICE_H
#define PROFILESERVICE_H

#include "easy_import.h"
#include "itokenvalueprovider.h"
#include "restapi.h"

#include "getprofile.h"
#include "eraseall.h"
#include "editprofile.h"

class ProfileService {
    shared_ptr<RestApi> restApi;
    shared_ptr<ITokenValueProvider> tokenValueProvider;
public:
    explicit ProfileService(shared_ptr<RestApi> restApi, shared_ptr<ITokenValueProvider> tokenValueProvider)
        : restApi { restApi }
        , tokenValueProvider { tokenValueProvider }
    { qDebug(); }
    ~ProfileService() { qDebug(); }

    auto * getProfile() {
        return restApi->execute<GetProfileResponse>(
            GetProfileRequest(),
            tokenValueProvider->tokenValue()
        );
    }

    auto * updateProfile(QString const & firstName,
                         QString const & lastName,
                         QString const & about
    ) {
        return restApi->execute<EditProfileResponse>(
            EditProfileRequest(firstName, lastName, about),
            tokenValueProvider->tokenValue()
        );
    }

    auto * eraseAll() {
        return restApi->execute<EraseAllResponse>(
            EraseAllRequest(),
            tokenValueProvider->tokenValue()
        );
    }
};

#endif // PROFILESERVICE_H
