#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QAbstractListModel>

#include "todosservice.h"

#include "edittodovm.h"

class ToDoListVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void showToDo(QString toDoId);
    void addToDo();
    void showUsersList();
    void showSettings();
    void visibilityChanged(bool isOwn);

public slots:
    void reloadRequired(QString const & toDoId) { loadToDos(); }

private:
    shared_ptr<ToDosService> m_service;
    bool isOwn = true;
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

    Q_INVOKABLE void callAddToDo() { emit addToDo(); }

    Q_INVOKABLE void changeVisibility() {
        isOwn = !isOwn;
        emit visibilityChanged(isOwn);
        loadToDos();
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
            updateNecessary(move(response->todos));

//            auto oldNum = m_todos.size();
//            if (oldNum == 0) {
//                qDebug() << "own 1";
//                beginResetModel();
//                m_todos = move(response->todos);
//                endResetModel();
//                return;
//            }

//            auto newNum = response->todos.size();
//            if (oldNum > newNum) {
//                qDebug() << "own 2";
//                beginRemoveRows(QModelIndex(), newNum, oldNum - 1);
//                m_todos = move(response->todos);
//                endRemoveRows();
//            } else if (oldNum < newNum) {
//                qDebug() << "own 3";
//                beginInsertRows(QModelIndex(), oldNum, newNum-1);
//                m_todos = move(response->todos);
//                endInsertRows();
//            }
//            emit dataChanged(createIndex(0, 0), createIndex(newNum, 0));

//            beginResetModel();
//            m_todos = move(response->todos);
//            endResetModel();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void loadAllToDos() {
        resOrErr(m_service->getAllToDos(), this,
        [this](auto * response) {
            updateNecessary(move(response->todos));
//            auto oldNum = m_todos.size();
//            if (oldNum == 0) {
//                qDebug() << "all 1";
//                beginResetModel();
//                m_todos = move(response->todos);
//                endResetModel();
//                return;
//            }

//            auto newNum = response->todos.size();
//            if (oldNum > newNum) {
//                qDebug() << "all 2";
//                beginRemoveRows(QModelIndex(), newNum, oldNum - 1);
//                m_todos = move(response->todos);
//                endRemoveRows();
//            } else if (oldNum < newNum) {
//                qDebug() << "all 3";
//                beginInsertRows(QModelIndex(), oldNum, newNum - 1);
//                m_todos = move(response->todos);
//                endInsertRows();
//            }
//            emit dataChanged(createIndex(0, 0), createIndex(newNum, 0));


//            beginResetModel();
//            m_todos = move(response->todos);
//            endResetModel();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void updateNecessary(vector<ToDoDto> const && todos) {
        auto oldNum = m_todos.size();
        if (oldNum == 0) {
            beginResetModel();
            m_todos = move(todos);
            endResetModel();
            return;
        }

        auto newNum = todos.size();
        if (oldNum > newNum) {
            beginRemoveRows(QModelIndex(), newNum, oldNum - 1);
            m_todos = move(todos);
            endRemoveRows();
        } else if (oldNum < newNum) {
            beginInsertRows(QModelIndex(), oldNum, newNum - 1);
            m_todos = move(todos);
            endInsertRows();
        }
        emit dataChanged(createIndex(0, 0), createIndex(newNum, 0));
    }
};

#endif // TODOLISTVM_H
