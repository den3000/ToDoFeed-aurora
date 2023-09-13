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
        auto * watcher = restApi->registration();;
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<UserDto>(&result)) {
                qDebug() << "user: " << *pData<< "\n";
            } else  if (const auto pError = get_if<RestError>(&result)) {
                switch (*pError) {
                case RestError::NetworkError: qDebug() << "NetworkError"; break;
                case RestError::SslError: qDebug() << "SslError"; break;
                }
            }
            watcher->deleteLater();
        });
    };
    
    Q_INVOKABLE void executeGetAllUsers() {
        auto * watcher = restApi->getAllUsers();;
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<vector<UserDto>>(&result)) {
                for(UserDto const & user : *pData) {
                    qDebug() << "user: " << user << "\n";
                }
            } else  if (const auto pError = get_if<RestError>(&result)) {
                switch (*pError) {
                case RestError::NetworkError: qDebug() << "NetworkError"; break;
                case RestError::SslError: qDebug() << "SslError"; break;
                }
            }
            watcher->deleteLater();
        });
    };

    Q_INVOKABLE void executeEditProfile() {
        auto * watcher = restApi->editProfile();;
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<UserDto>(&result)) {
                qDebug() << "user: " << *pData<< "\n";
            } else  if (const auto pError = get_if<RestError>(&result)) {
                switch (*pError) {
                case RestError::NetworkError: qDebug() << "NetworkError"; break;
                case RestError::SslError: qDebug() << "SslError"; break;
                }
            }
            watcher->deleteLater();
        });
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

signals:

};

#endif // RESTAPITESTVM_H
