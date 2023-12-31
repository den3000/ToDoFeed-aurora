#ifndef RESTAPI_H
#define RESTAPI_H

#include <QObject>

#include <QtNetwork>
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QThread>

#include "restapitypes.h"

#include "userdto.h"
#include "tododto.h"

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
    {
        // TODO: inject token properly
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        auto t = settings.value("token").toString();
        this->token = t;
        qDebug() << "token is" << this->token;
    };

    ~RestApi() {
        delete manager;
    }

    template<class T, typename=enable_if_t<is_base_of<RestApiResponse,T>::value>>
    RestResultWatcher<T> * execute(RestApiRequest const & request, optional<QString> token = nullopt, RestResultWatcher<T> * watcher = new RestResultWatcher<T>()) {
        QNetworkRequest networkRequest;
        if (token.has_value()) {
            networkRequest.setUrl(endpoint + request.endpoint() + "?token=" + token.value());
        } else {
            networkRequest.setUrl(endpoint + request.endpoint());
        }
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *reply;
        switch (request.reqType()) {
        case RestReqType::GET:
            reply = manager->get(networkRequest);
            break;
        case RestReqType::POST:
            QJsonObject obj;
            request.fill(obj);
            QJsonDocument doc(obj);
            QByteArray data = doc.toJson();
            reply = manager->post(networkRequest, data);
            break;
        }

        connect(reply, &QNetworkReply::finished, this, [watcher, reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                auto f = QtConcurrent::run([](){
                    return RestResult<T>(RestError::NullResponse);
                });
                watcher->setFuture(f);
                return;
            }

            if (jdReply.isEmpty()) {
                auto f = QtConcurrent::run([](){
                    return RestResult<T>(RestError::EmptyJsonResponse);
                });
                watcher->setFuture(f);
                return;
            }

            auto f = QtConcurrent::run([](QJsonDocument const &jd){
                    // TODO: probably mem usage might be imporved here with ptrs or refs
                    auto model = T();
                    auto result = model.parse(jd);
                    if (result) {
                        return RestResult<T>(model);
                    } else {
                        qDebug() << model.error();
                        return RestResult<T>(RestError::JsonParsingError);
                    }
            }, jdReply);

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            qDebug() << "request error: " << reply->errorString();
            auto f = QtConcurrent::run([](){
                return RestResult<T>(RestError::NetworkError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            qDebug() << "request sslErrors: " << reply->errorString();
            auto f = QtConcurrent::run([](){
                return RestResult<T>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    /* Left here for historical reasons

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

            // TODO: save this outside (in VM)
            QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
            settings.setValue("token", QVariant::fromValue(token));

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
            watcher->setFuture(f);
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

    RestResultWatcher<UserDto> * editProfile(RestResultWatcher<UserDto> * watcher = new RestResultWatcher<UserDto>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/edit_profile");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject obj;
        obj["token"] = token;
        obj["firstName"] = "John edited";
        obj["lastName"] = "Doe";
        obj["about"] = "Blockbuster MegaSuperStar";
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

        connect(reply, &QNetworkReply::finished, this, [watcher, reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                qDebug() << "json doc is null";
                return;
            }
            qDebug() << "editProfile response: " << jdReply;

            auto f = QtConcurrent::run([](QJsonObject const &jo){
                    auto user = UserDto(jo);
                    return RestResult<UserDto>(user);
            }, jdReply.object());

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "editProfile error";
            auto f = QtConcurrent::run([](){
                return RestResult<UserDto>(RestError::NetworkError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "editProfile sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<UserDto>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    RestResultWatcher<ToDoDto> * addToDo(RestResultWatcher<ToDoDto> * watcher = new RestResultWatcher<ToDoDto>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/add_todo");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject obj;
        obj["token"] = token;
        obj["title"] = "Buy some milk";
        obj["description"] = "Get that ffff milk";
        obj["status"] = "todo";
        obj["visibility"] = "public";

        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

        connect(reply, &QNetworkReply::finished, this, [watcher, reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                qDebug() << "json doc is null";
                return;
            }
            qDebug() << "response: " << jdReply;

            auto f = QtConcurrent::run([](QJsonObject const &jo){
                    auto user = ToDoDto(jo);
                    return RestResult<ToDoDto>(user);
            }, jdReply.object());

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "error";
            auto f = QtConcurrent::run([](){
                return RestResult<ToDoDto>(RestError::NetworkError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<ToDoDto>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };
    
    RestResultWatcher<vector<ToDoDto>> * getMyToDos(RestResultWatcher<vector<ToDoDto>> * watcher = new RestResultWatcher<vector<ToDoDto>>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/get_my_todos");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject obj;
        obj["token"] = token;
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

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
                    vector<ToDoDto> models;
                    for(QJsonValue const & value : ja) {
                        qDebug() << value;
                        ToDoDto model(value.toObject());
                        models.emplace_back(model);
                    }
                    return RestResult<vector<ToDoDto>>(models);
            }, jaReply);

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "getAllUsers error";
            auto f = QtConcurrent::run([](){
                return RestResult<vector<ToDoDto>>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "getAllUsers sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<vector<ToDoDto>>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    RestResultWatcher<vector<ToDoDto>> * getAllToDos(RestResultWatcher<vector<ToDoDto>> * watcher = new RestResultWatcher<vector<ToDoDto>>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/get_my_and_public_todos");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject obj;
        obj["token"] = token;
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

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
                    vector<ToDoDto> models;
                    for(QJsonValue const & value : ja) {
                        qDebug() << value;
                        ToDoDto model(value.toObject());
                        models.emplace_back(model);
                    }
                    return RestResult<vector<ToDoDto>>(models);
            }, jaReply);

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "getAllUsers error";
            auto f = QtConcurrent::run([](){
                return RestResult<vector<ToDoDto>>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "getAllUsers sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<vector<ToDoDto>>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    RestResultWatcher<ToDoDto> *  editToDo(RestResultWatcher<ToDoDto> * watcher = new RestResultWatcher<ToDoDto>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/edit_todo");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject obj;
        obj["token"] = token;
        obj["id"] = "83fd36c0-bcb3-4c5b-b136-39b69c2d32c8";
        obj["title"] = "Buy some milk!!!";
        obj["description"] = "GET THAT FFFF MILK";
        obj["status"] = "in_progress";
        obj["visibility"] = "private";
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();

        QNetworkReply *reply = manager->post(request, data);

        connect(reply, &QNetworkReply::finished, this, [watcher, reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                qDebug() << "json doc is null";
                return;
            }
            qDebug() << "editProfile response: " << jdReply;

            auto f = QtConcurrent::run([](QJsonObject const &jo){
                    auto user = ToDoDto(jo);
                    return RestResult<ToDoDto>(user);
            }, jdReply.object());

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "editProfile error";
            auto f = QtConcurrent::run([](){
                return RestResult<ToDoDto>(RestError::NetworkError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "editProfile sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<ToDoDto>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

    RestResultWatcher<QString> * eraseAll(RestResultWatcher<QString> * watcher = new RestResultWatcher<QString>()) {
        QNetworkRequest request;
        request.setUrl(endpoint + "/erase_all");
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [this, watcher, reply]() {
            QByteArray content = reply->readAll();
            auto jdReply = QJsonDocument::fromJson(content);
            if (jdReply.isNull()) {
                qDebug() << "json doc is null";
                return;
            }
            qDebug() << "editProfile response: " << jdReply;

            // TODO: remove this outside (in VM)
            QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
            settings.remove("token");
            token = "";

            auto f = QtConcurrent::run([](){
                    return RestResult<QString>("ok");
            });

            watcher->setFuture(f);
        });

        connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [reply, watcher](){
            Q_UNUSED(reply)
            qDebug() << "editProfile error";
            auto f = QtConcurrent::run([](){
                return RestResult<QString>(RestError::NetworkError);
            });
            watcher->setFuture(f);
        });

        connect(reply, &QNetworkReply::sslErrors, this, [reply, watcher]() {
            Q_UNUSED(reply)
            qDebug() << "editProfile sslErrors";
            auto f = QtConcurrent::run([](){
                return RestResult<QString>(RestError::SslError);
            });
            watcher->setFuture(f);
        });

        return watcher;
    };

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
*/
signals:

};
#endif // RESTAPI_H
