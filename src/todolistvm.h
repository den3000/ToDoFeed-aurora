#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QObject>
#include "edittodovm.h"

class ToDoListVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT

public:
    explicit ToDoListVM(QObject *parent = nullptr): QObject(parent) { };

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }

    Q_INVOKABLE void callAddToDo() {
        emit addToDo(this);
    };

signals:
    void showToDo(QString toDoId);
    void addToDo(IEditToDoDelegate * delegate);
    void showUsersList();
    void showSettings();

};

#endif // TODOLISTVM_H
