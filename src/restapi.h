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

enum class RestError { NetworkError, SslError };

template <typename Result>
using RestResult = variant<Result, RestError>;

template <typename Result>
using RestResultWatcher = QFutureWatcher<RestResult<Result>>;

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

    RestResultWatcher<UserDto> * registration(RestResultWatcher<UserDto> * watcher = new RestResultWatcher<UserDto>()) {
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

        connect(reply, &QNetworkReply::finished, this, [this, watcher, reply]() {
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

            auto f = QtConcurrent::run([](QJsonObject const &jo){
                    auto user = UserDto(jo);
                    return RestResult<UserDto>(user);
            }, joObject);

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "registration error";
            auto f = QtConcurrent::run([](){
                return RestResult<UserDto>(RestError::NetworkError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "registration sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<UserDto>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    RestResultWatcher<vector<UserDto>> * getAllUsers(RestResultWatcher<vector<UserDto>> * watcher = new RestResultWatcher<vector<UserDto>>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/get_all_users");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [reply, watcher]() {
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

            auto f = QtConcurrent::run([](QJsonArray const &ja){
                    vector<UserDto> models;
                    for(QJsonValue const & value : ja) {
                        qDebug() << value;
                        UserDto model(value.toObject());
                        models.emplace_back(model);
                    }
                    return RestResult<vector<UserDto>>(models);
            }, jaReply);

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "getAllUsers error";
            auto f = QtConcurrent::run([](){
                return RestResult<vector<UserDto>>(RestError::SslError);
            });
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "getAllUsers sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<vector<UserDto>>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    void addToDo() { qDebug() << "pam"; };
    void getAllToDos() { qDebug() << "pam"; };
    void getMyToDos() { qDebug() << "pam"; };
    void editToDo() { qDebug() << "pam"; };
    void editProfile() { qDebug() << "pam"; };

    void registrationOld() {
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

    void getAllUsersOld() {
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
