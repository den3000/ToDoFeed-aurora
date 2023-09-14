#ifndef HOMEVM_H
#define HOMEVM_H

#include <QObject>

class HomeVM : public QObject
{
    Q_OBJECT

public:
    explicit HomeVM(QObject *parent = nullptr): QObject(parent) { };

    Q_INVOKABLE void logoutPressed() { emit logout(); };

signals:
    void logout();

};

#endif // HOMEVM_H
