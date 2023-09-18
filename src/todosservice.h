#ifndef TODOSSERVICE_H
#define TODOSSERVICE_H

#include "easy_import.h"
#include "itokenvalueprovider.h"
#include "restapi.h"

#include "addtodo.h"
#include "edittodo.h"
#include "gettododetails.h"
#include "gettodoslist.h"

class ToDosService {
    shared_ptr<RestApi> restApi;
    shared_ptr<ITokenValueProvider> tokenValueProvider;
public:
    ToDosService(shared_ptr<RestApi> restApi, shared_ptr<ITokenValueProvider> tokenValueProvider)
        : restApi { restApi }
        , tokenValueProvider { tokenValueProvider }
    { qDebug(); };
    ~ToDosService() { qDebug(); }

    auto * addToDo(QString const & title,
                   QString const & description,
                   ToDoDto::Status status,
                   ToDoDto::Visibility visibility
    ) {
        return restApi->execute<AddToDoResponse>(
            AddToDoRequest(title, description, status, visibility),
            tokenValueProvider->tokenValue()
        );
    };

    auto * getToDoDetails(QString const & toDoId){
        return restApi->execute<GetToDoDetailsResponse>(
            GetToDoDetailsRequest(toDoId),
            tokenValueProvider->tokenValue()
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
            tokenValueProvider->tokenValue()
        );
    };

    auto * getMyToDos(){
        return restApi->execute<GetToDosListResponse>(
            GetToDosListRequest(),
            tokenValueProvider->tokenValue()
        );
    };

    auto * getAllToDos(){
        return restApi->execute<GetToDosListResponse>(
            GetToDosListRequest(false),
            tokenValueProvider->tokenValue()
        );
    };

    auto * getUserToDos(QString const & userId){
        return restApi->execute<GetToDosListResponse>(
            GetToDosListRequest(false, userId),
            tokenValueProvider->tokenValue()
        );
    };
};

#endif // TODOSSERVICE_H
