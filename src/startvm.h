#ifndef STARTVM_H
#define STARTVM_H

#include <QObject>

class StartVM : public QObject
{
    Q_OBJECT

public:
    explicit StartVM(QObject *parent = nullptr): QObject(parent) { };

    Q_INVOKABLE void loginPressed() { emit login(); };
    Q_INVOKABLE void signupPressed() { emit signup(); };

signals:
    void login();
    void signup();
};

#endif // STARTVM_H
