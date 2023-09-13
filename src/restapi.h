#ifndef RESTAPI_H
#define RESTAPI_H

#include <QObject>
#include <QtNetwork>

#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QThread>

#include "easy_import.h"

class RestApi : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *manager;
    QString endpoint;

public:
    explicit RestApi(QString const & endpoint, QObject *parent = nullptr)
        : QObject(parent)
        , manager { new QNetworkAccessManager(this) }
        , endpoint { endpoint }
    {};

    void registration() { qDebug() << "pam"; };
    void addToDo() { qDebug() << "pam"; };
    void getAllToDos() { qDebug() << "pam"; };
    void getMyToDos() { qDebug() << "pam"; };
    void editToDo() { qDebug() << "pam"; };
    void editProfile() { qDebug() << "pam"; };
    void getAllUsers() { qDebug() << "pam"; };

signals:

};
#endif // RESTAPI_H
