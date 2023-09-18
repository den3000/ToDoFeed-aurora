#ifndef USERSLISTVM_H
#define USERSLISTVM_H

#include <QAbstractListModel>

#include "usersservice.h"

#include "userdto.h"

class UsersListVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void viewUserDetails(QString userId);

private:
    shared_ptr<UsersService> m_service;
    vector<UserDto> m_users;

public:
    enum ToDoRoles {
        Title = Qt::UserRole + 1,
        UserId = Qt::UserRole + 2,
    };
    Q_ENUM(ToDoRoles)

    explicit UsersListVM(QObject *parent = nullptr): QAbstractListModel(parent) { qDebug(); };
    explicit UsersListVM(shared_ptr<UsersService> service, QObject *parent = nullptr)
        : QAbstractListModel(parent)
        , m_service { service }
    { qDebug(); };
    ~UsersListVM() { qDebug(); }

    Q_INVOKABLE void start() {
        loadUsers();
    }

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &) const override { return m_users.size(); }

    QVariant data(const QModelIndex &index, int role) const override {
        if(!index.isValid()) return QVariant();
        switch (role) {
        case Title: return QVariant(m_users[index.row()].fullName()); break;
        case UserId: return QVariant(m_users[index.row()].id); break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Title] = "title";
        roles[UserId] = "userId";
        return roles;
    }

private:
    void loadUsers() {
        resOrErr(m_service->getUsers(), this,
        [this](auto * response) {
            qDebug() << "get all users";
            beginResetModel();
            m_users = move(response->users);
            endResetModel();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};


#endif // USERSLISTVM_H
