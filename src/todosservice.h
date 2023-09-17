#ifndef TODOSSERVICE_H
#define TODOSSERVICE_H

#include "easy_import.h"
#include "restapi.h"

#include "addtodo.h"
#include "edittodo.h"
#include "gettododetails.h"
#include "gettodoslist.h"

class ToDosService {
    shared_ptr<RestApi> restApi;
    QString token;
public:
    ToDosService(shared_ptr<RestApi> restApi, QString const & token)
        : restApi { restApi }
        , token { token }
    { qDebug(); };
    ~ToDosService() { qDebug(); }

    auto * addToDo(QString const & title,
                   QString const & description,
                   ToDoDto::Status status,
                   ToDoDto::Visibility visibility
    ) {
        return restApi->execute<AddToDoResponse>(
            AddToDoRequest(title, description, status, visibility),
            token
        );
    };

    auto * getToDoDetails(QString const & toDoId){
        return restApi->execute<GetToDoDetailsResponse>(
            GetToDoDetailsRequest(toDoId),
            token
        );
    };

    auto * editToDo(QString const & toDoId,
                  QString const & title,
                  QString const & description,
                  ToDoDto::Status status,
                  ToDoDto::Visibility visibility
    ){
        return restApi->execute<EditToDoResponse>(
            EditToDoRequest(toDoId, title, description, status, visibility),
            token
        );
    };

    auto * getMyToDos(){
        return restApi->execute<GetToDosListResponse>(
            GetToDosListRequest(),
            token
        );
    };

    auto * getAllToDos(){
        return restApi->execute<GetToDosListResponse>(
            GetToDosListRequest(false),
            token
        );
    };
};

#endif // TODOSSERVICE_H
