#ifndef USERDETAILSVM_H
#define USERDETAILSVM_H

#include <QObject>

#include "usersservice.h"
#include "todosservice.h"

class UserDetailsVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void showToDo(QString const & toDoId);
    void userDetailsLoaded(QString const & userName);

private:
    shared_ptr<UsersService> m_userService;
    shared_ptr<ToDosService> m_toDosService;
    QString m_userId;
    vector<ToDoDto> m_todos;

public:
    explicit UserDetailsVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit UserDetailsVM(shared_ptr<UsersService> userService, shared_ptr<ToDosService> toDosService, QString const & userId, QObject *parent = nullptr)
        : QObject(parent)
        , m_userService { userService }
        , m_toDosService { toDosService }
        , m_userId { userId }
    { qDebug(); };
    ~UserDetailsVM() { qDebug(); }

    Q_INVOKABLE void start() {
        loadUserDetails();
        loadUserToDos();
    }

private:
    void loadUserDetails() {
        resOrErr(m_userService->getUserDetails(m_userId), this,
        [this](auto * response){
            emit userDetailsLoaded(response->user.fullName());
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void loadUserToDos() {
        resOrErr(m_toDosService->getUserToDos(m_userId), this,
        [this](auto * response) {
            m_todos = move(response->todos);
            for(ToDoDto & toDo : m_todos) {
                qDebug() << "todo: " << toDo;
            }
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};

#endif // USERDETAILSVM_H
