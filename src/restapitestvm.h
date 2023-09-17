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
#include "gettodoslist.h"
#include "gettododetails.h"
#include "edittodo.h"

class RestApiTestVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

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
//            "zxcv7890",
//            "Jane",
//            "Doe",
//            "Celebrity"
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
            qDebug() << "todo\n" << response->toDo << "\n";
        }, [](auto * error){
            Q_UNUSED(error)
        });
    };
    
    Q_INVOKABLE void executeGetMyToDos() {
//        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
//        QString t = settings.value("token").toString();

//        auto * watcher = restApi->execute<GetToDosListResponse>(GetToDosListRequest(), t);
//        resOrErr(watcher, this, [](auto * response){
//            qDebug() << "get my todos";
//            for(ToDoDto const & user : response->todos) {
//                qDebug() << "todo\n" << user << "\n";
//            }
//        }, [](auto * error){
//            Q_UNUSED(error)
//        });
    };

    Q_INVOKABLE void executeGetAllToDos() {
//        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
//        QString t = settings.value("token").toString();

//        auto * watcher = restApi->execute<GetAllToDosResponse>(GetAllToDosRequest(), t);
//        resOrErr(watcher, this, [](auto * response){
//            qDebug() << "get all todos";
//            for(ToDoDto const & user : response->todos) {
//                qDebug() << "todo\n" << user << "\n";
//            }
//        }, [](auto * error){
//            Q_UNUSED(error)
//        });
    };
    
    Q_INVOKABLE void executeEditToDo() {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        QString t = settings.value("token").toString();

        auto * watcher = restApi->execute<EditToDoResponse>(EditToDoRequest(
            "c4f709f2-b295-4487-8848-d561de3301c2",
            "Buy some milk",
            "Get that ffff milk",
            ToDoDto::Status::InProgress,
            ToDoDto::Visibility::Own
        ), t);
        resOrErr(watcher, this, [](auto * response){
            qDebug() << "edit todo";
            qDebug() << "todo\n" << response->toDo << "\n";
        }, [](auto * error){
            Q_UNUSED(error)
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
