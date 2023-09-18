#ifndef USERDETAILSVM_H
#define USERDETAILSVM_H

#include <QAbstractListModel>

#include "usersservice.h"
#include "todosservice.h"

class UserDetailsVM :public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void showToDo(QString const & toDoId);
    void userDetailsLoaded(QString const & userName);

private:
    shared_ptr<UsersService> m_userService;
    shared_ptr<ToDosService> m_toDosService;
    QString m_userId;
    vector<ToDoDto> m_todos;

public:
    enum ToDoRoles {
        Title = Qt::UserRole + 1,
        Status = Qt::UserRole + 2,
        ToDoId = Qt::UserRole + 3,
        UserId = Qt::UserRole + 4,
        Visibility = Qt::UserRole + 5,
    };
    Q_ENUM(ToDoRoles)

    explicit UserDetailsVM(QObject *parent = nullptr): QAbstractListModel(parent) { qDebug(); };
    explicit UserDetailsVM(shared_ptr<UsersService> userService, shared_ptr<ToDosService> toDosService, QString const & userId, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_userService { userService }
        , m_toDosService { toDosService }
        , m_userId { userId }
    { qDebug(); };
    ~UserDetailsVM() { qDebug(); }

    Q_INVOKABLE void start() {
        loadUserDetails();
        loadUserToDos();
    }

    // QAbstractItemModel interface
    // TODO: extract into separate class
    int rowCount(const QModelIndex &) const override { return m_todos.size(); }

    QVariant data(const QModelIndex &index, int role) const override {
        if(!index.isValid()) return QVariant();
        switch (role) {
        case Title: return QVariant(m_todos[index.row()].title); break;
        case Status: return QVariant(m_todos[index.row()].statusStr()); break;
        case ToDoId: return QVariant(m_todos[index.row()].id); break;
        case UserId: return QVariant(m_todos[index.row()].userId); break;
        case Visibility: return QVariant(m_todos[index.row()].visibilityStr()); break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Title] = "title";
        roles[Status] = "status";
        roles[ToDoId] = "toDoId";
        roles[UserId] = "userId";
        roles[Visibility] = "visibility";
        return roles;
    }

private:
    void loadUserDetails() {
        resOrErr(m_userService->getUserDetails(m_userId), this,
        [this](auto * response){
            emit userDetailsLoaded(response->user.fullName());
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void loadUserToDos() {
        resOrErr(m_toDosService->getUserToDos(m_userId), this,
        [this](auto * response) {
            beginResetModel();
            m_todos = move(response->todos);
            endResetModel();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};

#endif // USERDETAILSVM_H
