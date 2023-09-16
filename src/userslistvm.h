#ifndef USERSLISTVM_H
#define USERSLISTVM_H

#include <QObject>

#include "usersservice.h"

class UsersListVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    shared_ptr<UsersService> m_service;

public:
    explicit UsersListVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit UsersListVM(shared_ptr<UsersService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_service { service }
    { qDebug(); };
    ~UsersListVM() { qDebug(); }

signals:
    void viewUserDetails(QString userId);
};


#endif // USERSLISTVM_H
