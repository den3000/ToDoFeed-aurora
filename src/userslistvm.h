#ifndef USERSLISTVM_H
#define USERSLISTVM_H

#include <QObject>

class UsersListVM : public QObject
{
    Q_OBJECT

public:
    explicit UsersListVM(QObject *parent = nullptr): QObject(parent) { };

signals:
    void viewUserDetails();
};


#endif // USERSLISTVM_H
