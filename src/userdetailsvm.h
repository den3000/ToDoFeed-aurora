#ifndef USERDETAILSVM_H
#define USERDETAILSVM_H

#include <QObject>

class UserDetailsVM : public QObject
{
    Q_OBJECT

public:
    explicit UserDetailsVM(QObject *parent = nullptr): QObject(parent) { };

signals:
    void showToDo(QString const & toDoId);
};

#endif // USERDETAILSVM_H
