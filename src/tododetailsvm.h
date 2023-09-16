#ifndef TODODETAILSVM_H
#define TODODETAILSVM_H

#include <QObject>
#include "edittodovm.h"

class ToDoDetailsVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    QString toDoId;

public:
    explicit ToDoDetailsVM(QObject *parent = nullptr): QObject(parent) { };
    explicit ToDoDetailsVM(QString const & toDoId, QObject *parent = nullptr)
        : QObject(parent)
        , toDoId { toDoId }
    { };

    Q_INVOKABLE QString title() { return "title" + toDoId; }
    Q_INVOKABLE QString details() { return "details " + toDoId; }
    Q_INVOKABLE QString status() { return "status " + toDoId; }
    Q_INVOKABLE QString visibility() { return "visibility " + toDoId; }

    Q_INVOKABLE void onEditToDo() {
        emit editToDo(toDoId, this);
    };

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }
signals:
    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate);
};

#endif // TODODETAILSVM_H
