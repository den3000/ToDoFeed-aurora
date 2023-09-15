#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QObject>

class ToDoListVM : public QObject
{
    Q_OBJECT

public:
    explicit ToDoListVM(QObject *parent = nullptr): QObject(parent) { };

signals:
    void showToDo();
    void editToDo();
    void showUsersList();
    void showSettings();
};

#endif // TODOLISTVM_H
