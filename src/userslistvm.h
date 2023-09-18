#ifndef USERSLISTVM_H
#define USERSLISTVM_H

#include <QObject>

#include "usersservice.h"

#include "userdto.h"

class UsersListVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void viewUserDetails(QString userId);

private:
    shared_ptr<UsersService> m_service;
    vector<UserDto> m_users;

public:
    explicit UsersListVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit UsersListVM(shared_ptr<UsersService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_service { service }
    { qDebug(); };
    ~UsersListVM() { qDebug(); }

    Q_INVOKABLE void start() {
        loadUsers();
    }

private:
    void loadUsers() {
        resOrErr(m_service->getUsers(), this,
        [this](auto * response) {
            qDebug() << "get all users";
            m_users = move(response->users);
            for(UserDto const & user : m_users) {
                qDebug() << "user\n" << user << "\n";
            }
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};


#endif // USERSLISTVM_H
