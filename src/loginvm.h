#ifndef LOGINVM_H
#define LOGINVM_H

#include <QObject>

class LoginVM : public QObject
{
    Q_OBJECT

public:
    explicit LoginVM(QObject *parent = nullptr): QObject(parent) { };

    Q_INVOKABLE void loginPressed() { emit authorized("login_token_value"); };

signals:
    void authorized(QString const & token);
};

#endif // LOGINVM_H
