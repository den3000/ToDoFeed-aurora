#ifndef HOMEVM_H
#define HOMEVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogouttokenprovider.h"

class HomeVM : public QObject
{
    Q_OBJECT
    shared_ptr<ILogoutTokenProvider> tokenProvider;

public:
    explicit HomeVM(QObject *parent = nullptr): QObject(parent) { };
    explicit HomeVM(shared_ptr<ILogoutTokenProvider> tokenProvider, QObject *parent = nullptr)
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

#endif // HOMEVM_H
