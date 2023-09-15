#ifndef TODODETAILSVM_H
#define TODODETAILSVM_H

#include <QObject>

class ToDoDetailsVM : public QObject
{
    Q_OBJECT

public:
    explicit ToDoDetailsVM(QObject *parent = nullptr): QObject(parent) { };

signals:
    void editToDo();
};

#endif // TODODETAILSVM_H
