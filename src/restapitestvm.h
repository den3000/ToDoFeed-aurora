#ifndef RESTAPITESTVM_H
#define RESTAPITESTVM_H

#include <QObject>
#include "restapi.h"

class RestApiTestVM : public QObject
{
    Q_OBJECT

    RestApi * restApi;

public:
    explicit RestApiTestVM(QObject *parent = nullptr): QObject(parent) { };
    explicit RestApiTestVM(RestApi * restApi, QObject *parent = nullptr)
        : QObject { parent }
        , restApi { restApi }
    { };

    Q_INVOKABLE void executeRegister() {
        restApi->registration();
    };
    
    Q_INVOKABLE void executeAddToDo() {
        restApi->addToDo();
    };
    
    Q_INVOKABLE void executeGetAllToDos() {
        restApi->getAllToDos();
    };
    
    Q_INVOKABLE void executeGetMyToDos() {
        restApi->getMyToDos();
    };
    
    Q_INVOKABLE void executeEditToDo() {
        restApi->editToDo();
    };
    
    Q_INVOKABLE void executeEditProfile() {
        restApi->editProfile();
    };
    
    Q_INVOKABLE void executeGetAllUsers() {
        restApi->getAllUsers();
    };
    

signals:

};

#endif // RESTAPITESTVM_H
