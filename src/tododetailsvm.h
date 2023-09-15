#ifndef TODODETAILSVM_H
#define TODODETAILSVM_H

#include <QObject>
#include "edittodovm.h"

class ToDoDetailsVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT
    QString toDoId;

public:
    explicit ToDoDetailsVM(QObject *parent = nullptr): QObject(parent) { };
    explicit ToDoDetailsVM(QString const & toDoId, QObject *parent = nullptr)
        : QObject(parent)
        , toDoId { toDoId }
    { };

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }

    Q_INVOKABLE QString title() { return toDoId; }
    Q_INVOKABLE void callEditToDo(QString const & toDoId) {
        emit editToDo(toDoId, this);
    };

signals:
    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate);
};

#endif // TODODETAILSVM_H
