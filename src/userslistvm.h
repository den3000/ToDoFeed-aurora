#ifndef USERSLISTVM_H
#define USERSLISTVM_H

#include <QObject>

class UsersListVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit UsersListVM(QObject *parent = nullptr): QObject(parent) { };

signals:
    void viewUserDetails(QString userId);
};


#endif // USERSLISTVM_H
