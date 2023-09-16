#ifndef USERDETAILSVM_H
#define USERDETAILSVM_H

#include <QObject>

class UserDetailsVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    QString userId;

public:
    explicit UserDetailsVM(QObject *parent = nullptr): QObject(parent) { };
    explicit UserDetailsVM(QString const & userId, QObject *parent = nullptr)
        : QObject(parent)
        , userId { userId }
    { };

    Q_INVOKABLE QString userName() { return userId; }
signals:
    void showToDo(QString toDoId);
};

#endif // USERDETAILSVM_H
