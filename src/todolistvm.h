#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogouttokenprovider.h"

class ToDoListVM : public QObject
{
    Q_OBJECT
    shared_ptr<ILogoutTokenProvider> tokenProvider;

public:
    explicit ToDoListVM(QObject *parent = nullptr): QObject(parent) { };
    explicit ToDoListVM(shared_ptr<ILogoutTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , tokenProvider { tokenProvider }
    { };

    Q_INVOKABLE void logoutPressed() {
        tokenProvider.get()->logout();
        emit logout();
    };

signals:
    void logout();
};

#endif // TODOLISTVM_H
