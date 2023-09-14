#ifndef RESTAPITESTVM_H
#define RESTAPITESTVM_H

#include <QObject>
#include "restapi.h"
#include "getallusers.h"
#include "signup.h"
#include "login.h"
#include "editprofile.h"
#include "eraseall.h"
#include "addtodo.h"

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
    
    Q_INVOKABLE void executeLogin() {
        auto * watcher = restApi->execute<LogInResponse>(LogInRequest(
            "qwer123"
        ));
        resOrErr(watcher, this, [](auto * response){
            qDebug() << "log in";
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
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        QString t = settings.value("token").toString();

        auto * watcher = restApi->execute<EditProfileResponse>(EditProfileRequest(
            "John",
            "Doe",
            "Movie SuperStar"
        ), t);
        resOrErr(watcher, this, [](auto * response){
            qDebug() << "edit profile";
            qDebug() << "user\n" << response->user << "\n";
        }, [](auto * error){
            Q_UNUSED(error)
        });
    };

    Q_INVOKABLE void executeAddToDo() {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        QString t = settings.value("token").toString();

        auto * watcher = restApi->execute<AddToDoResponse>(AddToDoRequest(
            "Buy some milk",
            "Get that ffff milk",
            ToDoDto::Status::Todo,
            ToDoDto::Visibility::ForAll
        ), t);
        resOrErr(watcher, this, [](auto * response){
            qDebug() << "add todo";
            qDebug() << "todo\n" << response->todo << "\n";
        }, [](auto * error){
            Q_UNUSED(error)
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
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        QString t = settings.value("token").toString();

        auto * watcher = restApi->execute<EraseAllResponse>(EraseAllRequest(), t);
        resOrErr(watcher, this, [](auto * response){
            Q_UNUSED(response)
            qDebug() << "erase all on";
        }, [](auto * error){
            Q_UNUSED(error)
        });
    };

signals:

};

#endif // RESTAPITESTVM_H
