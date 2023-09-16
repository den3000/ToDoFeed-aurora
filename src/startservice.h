#ifndef STARTSERVICE_H
#define STARTSERVICE_H

#include "easy_import.h"
#include "restapi.h"

#include "login.h"

class StartService {
    shared_ptr<RestApi> restApi;

public:
    explicit StartService(shared_ptr<RestApi> restApi)
        : restApi { restApi }
    { qDebug(); };
    ~StartService() { qDebug(); }

    auto * login(QString const & password)
        { return restApi->execute<LogInResponse>(LogInRequest(password)); };

    void signup(){

    };
};
#endif // STARTSERVICE_H
