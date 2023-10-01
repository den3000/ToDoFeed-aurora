#ifndef DICONSUMER_H
#define DICONSUMER_H

#include <QObject>
#include "diprovider.h"

class DiConsumer: public QObject {
    Q_OBJECT

    DiProvider diProvider;

    shared_ptr<StartService> m_startService;
    shared_ptr<StartService> lazyStartService() {
        if(!m_startService) {
            m_startService = diProvider.startServiceInstance();
        }
        return m_startService;
    };

    shared_ptr<ToDosService> m_toDoService = diProvider.todosServiceInstance();
    shared_ptr<UsersService> m_usersService = diProvider.usersServiceInstance();
    shared_ptr<ProfileService> m_profileService;
    shared_ptr<ProfileService> lazyProfileService() {
        if(!m_profileService) {
            m_profileService = diProvider.profileServiceInstance();
        }
        return m_profileService;
    };

public:

    explicit DiConsumer(QObject * parent = nullptr)
        : QObject(parent)
    { qDebug(); }
    ~DiConsumer() { qDebug(); }

    // Start flow -------------------

    Q_INVOKABLE bool isLoggedIn() { return diProvider.loginStateProvider()->isLoggedIn(); }

    Q_INVOKABLE StartVM * startVmInstance()
        { return unique_unwrap(diProvider.startVmInstance()); }

    Q_INVOKABLE LoginVM * loginVmInstance()
        { return unique_unwrap(diProvider.loginVmInstance(lazyStartService())); }

    Q_INVOKABLE EditProfileVM * signupVmInstance()
        { return unique_unwrap(diProvider.editProfileInstance(lazyStartService())); }

    // Home flow --------------------

    Q_INVOKABLE ToDoListVM * toDoListVmInstance()
        { return unique_unwrap(diProvider.toDoListVmInstance(m_toDoService)); }

    Q_INVOKABLE ToDoDetailsVM * toDoDetailsVmInstance(QString const & todoId)
        { return unique_unwrap(diProvider.toDoDetailsVmInstance(m_toDoService, todoId)); }

    Q_INVOKABLE EditToDoVM * editToDoVmInstance(QString const & toDoId)
        { return unique_unwrap(diProvider.editToDoVmInstance(m_toDoService, toDoId)); }

    Q_INVOKABLE UsersListVM * usersListVmInstance()
        { return unique_unwrap(diProvider.usersListVmInstance(m_usersService)); }

    Q_INVOKABLE UserDetailsVM * usersDetailsVmInstance(QString const & userId)
        { return unique_unwrap(diProvider.userDetailsVmInstance(m_usersService, m_toDoService, userId)); }

    Q_INVOKABLE EditProfileVM * editProfileVmInstance()
        { return unique_unwrap(diProvider.editProfileVmInstance(lazyProfileService())); }
};
#endif // DICONSUMER_H
