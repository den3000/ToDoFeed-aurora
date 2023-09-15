#ifndef STARTSERVICE_H
#define STARTSERVICE_H

#include "easy_import.h"
#include "restapi.h"

class StartService {
    shared_ptr<RestApi> restApi;

    StartService(shared_ptr<RestApi> restApi)
        : restApi { restApi }
    {};

    void login(){

    };

    void signup(){

    };
};
#endif // STARTSERVICE_H
