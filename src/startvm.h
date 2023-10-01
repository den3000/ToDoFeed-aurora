#ifndef STARTVM_H
#define STARTVM_H

#include <QObject>
#include <QDebug>

class StartVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent) // !!! IMPORTANT !!!

public:
    explicit StartVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    ~StartVM() { qDebug(); }

signals:
    void login();
    void signup();
};

#endif // STARTVM_H
