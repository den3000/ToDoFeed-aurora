#ifndef TODODTO_H
#define TODODTO_H

#include "easy_import.h"

struct ToDoDto
{
    // TODO: improve enums handling
    enum class Status { Todo, InProgress, Done };
    enum class Visibility { own, forAll };

    static optional<ToDoDto::Status> parse_status(QJsonValue && value) {
        auto s = value.toString();
        if (s == "todo") {
            return ToDoDto::Status::Todo;
        } else if (s == "in_progress") {
            return ToDoDto::Status::InProgress;
        } else if (s == "done") {
            return ToDoDto::Status::InProgress;
        } else {
            return nullopt;
        }
    }

    static optional<ToDoDto::Visibility> parse_visibility(QJsonValue && value) {
        auto s = value.toString();
        if (s == "public") {
            return ToDoDto::Visibility::forAll;
        } else if (s == "private") {
            return ToDoDto::Visibility::own;
        } else {
            return nullopt;
        }
    }

    QString id;
    QString userId;
    QString title;
    QString description;
    optional<ToDoDto::Status> status;
    optional<ToDoDto::Visibility> visibility;

    explicit ToDoDto(QString id, QString userId, QString title, QString description, ToDoDto::Status status, Visibility visibility)
        : id { move(id) }
        , userId { move(userId) }
        , title { move(title) }
        , description { move(description) }
        , status { move(status) }
        , visibility { move(visibility) }
    {};

    explicit ToDoDto(QJsonObject && json)
        : id { json["id"].toString() }
        , userId { json["userId"].toString() }
        , title { json["title"].toString() }
        , description { json["description"].toString() }
        , status { parse_status(json["status"]) }
        , visibility { parse_visibility(json["visibility"]) }
    {};

    friend QDebug & operator<<(QDebug & d, ToDoDto const & dto) {
        d << "id: " << dto.id << "\n"
            << "userId: " << dto.userId << "\n"
            << "title: " << dto.title << "\n"
            << "description: " << dto.description << "\n"
            << "status: " << dto.status << "\n"
            << "visibility: " << dto.visibility;
        return d;
    };
};

#endif // TODODTO_H
