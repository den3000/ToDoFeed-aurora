#ifndef USERDETAILSVM_H
#define USERDETAILSVM_H

#include <QObject>

#include "usersservice.h"

class UserDetailsVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    shared_ptr<UsersService> m_service;
    QString m_userId;

public:
    explicit UserDetailsVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit UserDetailsVM(shared_ptr<UsersService> service, QString const & userId, QObject *parent = nullptr)
        : QObject(parent)
        , m_service { service }
        , m_userId { userId }
    { qDebug(); };
    ~UserDetailsVM() { qDebug(); }

    Q_INVOKABLE QString userName() { return m_userId; }
signals:
    void showToDo(QString toDoId);
};

#endif // USERDETAILSVM_H
