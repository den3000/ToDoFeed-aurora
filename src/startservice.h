#ifndef STARTSERVICE_H
#define STARTSERVICE_H

#include "easy_import.h"
#include "restapi.h"

#include "login.h"
#include "signup.h"

class StartService {
    shared_ptr<RestApi> restApi;

public:
    explicit StartService(shared_ptr<RestApi> restApi)
        : restApi { restApi }
    { qDebug(); };
    ~StartService() { qDebug(); }

    auto * login(QString const & password)
        { return restApi->execute<LogInResponse>(LogInRequest(password)); };

    auto * signup(
        QString const & password,
        QString const & firstName,
        QString const & lastName,
        QString const & about
    ){
        return restApi->execute<SignUpResponse>(SignUpRequest(
            password,
            firstName,
            lastName,
            about
        ));
    };
};
#endif // STARTSERVICE_H
