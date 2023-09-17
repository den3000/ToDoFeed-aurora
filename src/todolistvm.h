#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QAbstractListModel>

#include "todosservice.h"

#include "edittodovm.h"

class ToDoListVM : public QAbstractListModel, public IEditToDoDelegate
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void showToDo(QString toDoId);
    void addToDo(IEditToDoDelegate * delegate);
    void showUsersList();
    void showSettings();
    void visibilityChanged(bool isOwn);

private:

    shared_ptr<ToDosService> m_service;
    bool isOwn = true;
    vector<ToDoDto> m_todos;

public:
    enum ToDoRoles {
        Title = Qt::UserRole + 1,
        Status = Qt::UserRole + 2,
        ToDoId = Qt::UserRole + 3,
    };
    Q_ENUM(ToDoRoles)

    explicit ToDoListVM(QObject *parent = nullptr): QAbstractListModel(parent) { qDebug(); }
    explicit ToDoListVM(shared_ptr<ToDosService> service, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_service{ service }
    { qDebug(); }
    ~ToDoListVM() { qDebug(); }

    Q_INVOKABLE void start() {
        emit visibilityChanged(isOwn);
        loadToDos();
    }

    Q_INVOKABLE void callAddToDo() { emit addToDo(this); }

    Q_INVOKABLE void changeVisibility() {
        isOwn = !isOwn;
        emit visibilityChanged(isOwn);
        loadToDos();
    }
    
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &) const override { return m_todos.size(); }

    QVariant data(const QModelIndex &index, int role) const override {
        if(!index.isValid()) return QVariant();
        switch (role) {
        case Title: return QVariant(m_todos[index.row()].title); break;
        case Status: return QVariant(m_todos[index.row()].statusStr()); break;
        case ToDoId: return QVariant(m_todos[index.row()].id); break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Title] = "title";
        roles[Status] = "status";
        roles[ToDoId] = "toDoId";
        return roles;
    }

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
        loadToDos();
    }

private:
    void loadToDos() {
        if (isOwn) {
            loadOwnToDos();
        } else {
            loadAllToDos();
        }
    }

    void loadOwnToDos() {
        resOrErr(m_service->getMyToDos(), this,
        [this](auto * response) {
            beginResetModel();
            m_todos = move(response->todos);
            endResetModel();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void loadAllToDos() {
        resOrErr(m_service->getAllToDos(), this,
        [this](auto * response) {
            beginResetModel();
            m_todos = move(response->todos);
            endResetModel();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};

#endif // TODOLISTVM_H
