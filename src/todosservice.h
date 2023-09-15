#ifndef TODOSSERVICE_H
#define TODOSSERVICE_H

#include "easy_import.h"
#include "restapi.h"

class ToDosService {
    shared_ptr<RestApi> restApi;
    QString token;

    ToDosService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    {};

    void addToDo(){

    };

    void editToDo(){

    };

    void getMyToDos(){

    };

    void getAllToDos(){

    };
};

#endif // TODOSSERVICE_H
