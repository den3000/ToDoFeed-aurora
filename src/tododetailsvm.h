#ifndef TODODETAILSVM_H
#define TODODETAILSVM_H

#include <QObject>
#include "edittodovm.h"

class ToDoDetailsVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT

public:
    explicit ToDoDetailsVM(QObject *parent = nullptr): QObject(parent) { };

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }

    Q_INVOKABLE void callEditToDo(QString const & toDoId) {
        emit editToDo(toDoId, this);
    };

signals:
    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate);
};

#endif // TODODETAILSVM_H
