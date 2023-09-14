#ifndef RESTAPITESTVM_H
#define RESTAPITESTVM_H

#include <QObject>
#include "restapi.h"
#include "getallusers.h"
#include "signup.h"

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
        auto * watcher = restApi->execute<SignUpResponse>(SignUpRequest(
            "qwer123",
            "John",
            "Doe",
            "Movie Star"
        ));
        resOrErr(watcher, this, [](auto * response){
            qDebug() << "sign up";
            qDebug() << "user\n" << response->user << "\n";

            QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
            settings.setValue("token", QVariant::fromValue(response->token));
        }, [](auto * error){
            Q_UNUSED(error)
        });
    };
    
    Q_INVOKABLE void executeGetAllUsers() {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        QString t = settings.value("token").toString();

        auto * watcher = restApi->execute<GetAllUsersResponse>(GetAllUsersRequest(), t);
        resOrErr(watcher, this, [](auto * response){
            qDebug() << "get all users";
            for(UserDto const & user : response->users) {
                qDebug() << "user\n" << user << "\n";
            }
        }, [](auto * error){
            Q_UNUSED(error)
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
        auto * watcher = restApi->addToDo();
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<ToDoDto>(&result)) {
                qDebug() << "todo: " << *pData<< "\n";
            } else  if (const auto pError = get_if<RestError>(&result)) {
                switch (*pError) {
                case RestError::NetworkError: qDebug() << "NetworkError"; break;
                case RestError::SslError: qDebug() << "SslError"; break;
                }
            }
            watcher->deleteLater();
        });
    };
    
    Q_INVOKABLE void executeGetMyToDos() {
        auto * watcher = restApi->getMyToDos();
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<vector<ToDoDto>>(&result)) {
                for(ToDoDto const & todo : *pData) {
                    qDebug() << "todo: " << todo << "\n";
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

    Q_INVOKABLE void executeGetAllToDos() {
        auto * watcher = restApi->getAllToDos();
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<vector<ToDoDto>>(&result)) {
                for(ToDoDto const & todo : *pData) {
                    qDebug() << "todo: " << todo << "\n";
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
    
    Q_INVOKABLE void executeEditToDo() {
        auto * watcher = restApi->editToDo();
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<ToDoDto>(&result)) {
                qDebug() << "todo: " << *pData<< "\n";
            } else  if (const auto pError = get_if<RestError>(&result)) {
                switch (*pError) {
                case RestError::NetworkError: qDebug() << "NetworkError"; break;
                case RestError::SslError: qDebug() << "SslError"; break;
                }
            }
            watcher->deleteLater();
        });
    };  

    Q_INVOKABLE void executeEraseAll() {
        auto * watcher = restApi->eraseAll();;
        connect(watcher, &QFutureWatcher<void>::finished, this, [watcher](){
            auto result = watcher->result();
            if (const auto pData = get_if<QString>(&result)) {
                qDebug() << "erase_all: " << *pData<< "\n";
            } else  if (const auto pError = get_if<RestError>(&result)) {
                switch (*pError) {
                case RestError::NetworkError: qDebug() << "NetworkError"; break;
                case RestError::SslError: qDebug() << "SslError"; break;
                }
            }
            watcher->deleteLater();
        });
    };

signals:

};

#endif // RESTAPITESTVM_H
