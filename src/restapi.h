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

#include "userdto.h"

class RestApi : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *manager;
    QString endpoint;
    QString token = "";

public:
    explicit RestApi(QString const & endpoint, QObject *parent = nullptr)
        : QObject(parent)
        , manager { new QNetworkAccessManager(this) }
        , endpoint { endpoint }
    {};

    void registration() {
        QNetworkRequest request;
        request.setUrl(endpoint + "/register");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject obj;
        obj["password"] = "qwer123";
        obj["firstName"] = "John";
        obj["lastName"] = "Doe";
        obj["about"] = "Movie Star";
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                qDebug() << "json doc is null";
                return;
            }
            qDebug() << "registration response: " << jdReply;

            auto joObject = jdReply.object();
            token = joObject["token"].toString();
            qDebug() << "token: " << token;
            // TODO: save token to some preferences files

            auto user = UserDto(move(joObject));
            qDebug() << "user model: " << user;
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply](){
            Q_UNUSED(reply)
            qDebug() << "registration error";
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply]() {
            Q_UNUSED(reply)
            qDebug() << "registration sslErrors";
        });
    };

    void addToDo() { qDebug() << "pam"; };
    void getAllToDos() { qDebug() << "pam"; };
    void getMyToDos() { qDebug() << "pam"; };
    void editToDo() { qDebug() << "pam"; };
    void editProfile() { qDebug() << "pam"; };

    void getAllUsers() {
        QNetworkRequest request;
        request.setUrl(endpoint + "/get_all_users");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                qDebug() << "json doc is null";
                return;
            }

            qDebug() << "get_all_users response: " << jdReply;

            auto jaReply = jdReply.array();
            if (jaReply.isEmpty()) {
                qDebug() << "json array is null";
                return;
            }

            vector<UserDto> models;
            for(QJsonValue const & value : jaReply) {
                qDebug() << value;
                UserDto model(value.toObject());
                models.emplace_back(model);
                qDebug() << "user model: " << model;
            }
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply](){
            qDebug() << "get_all_users error: " << reply->errorString();
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply]() {
            Q_UNUSED(reply)
            qDebug() << "get_all_users sslErrors: " << reply->errorString();
        });
    };

signals:

};
#endif // RESTAPI_H
