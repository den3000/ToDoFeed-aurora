#ifndef TODODTO_H
#define TODODTO_H

#include "easy_import.h"

struct ToDoDto
{
    // TODO: improve enums handling
    enum class Status { Todo, InProgress, Done };
    enum class Visibility { Own, ForAll };

    static QString status_to_string(ToDoDto::Status status) {
        switch (status) {
        case ToDoDto::Status::Todo: return "todo"; break;
        case ToDoDto::Status::InProgress: return "in_progress"; break;
        case ToDoDto::Status::Done: return "done"; break;
        }
    }
    static optional<ToDoDto::Status> parse_status(QJsonValue && value) {
        auto s = value.toString();
        if (s == "todo") {
            return ToDoDto::Status::Todo;
        } else if (s == "in_progress") {
            return ToDoDto::Status::InProgress;
        } else if (s == "done") {
            return ToDoDto::Status::Done;
        } else {
            return nullopt;
        }
    }

    static QString visibility_to_string(ToDoDto::Visibility status) {
        switch (status) {
        case ToDoDto::Visibility::Own: return "private"; break;
        case ToDoDto::Visibility::ForAll: return "public"; break;
        }
    }
    static optional<ToDoDto::Visibility> parse_visibility(QJsonValue && value) {
        auto s = value.toString();
        if (s == "public") {
            return ToDoDto::Visibility::ForAll;
        } else if (s == "private") {
            return ToDoDto::Visibility::Own;
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

    // default constructor to make it work with variant
    explicit ToDoDto()
        : id { "" }
        , userId { "" }
        , title { "" }
        , description { "" }
        , status { ToDoDto::Status::Todo }
        , visibility { ToDoDto::Visibility::Own }
    {};

    explicit ToDoDto(QString id, QString userId, QString title, QString description, ToDoDto::Status status, Visibility visibility)
        : id { move(id) }
        , userId { move(userId) }
        , title { move(title) }
        , description { move(description) }
        , status { move(status) }
        , visibility { move(visibility) }
    {};

    explicit ToDoDto(QJsonObject const & json)
        : id { json["id"].toString() }
        , userId { json["userId"].toString() }
        , title { json["title"].toString() }
        , description { json["description"].toString() }
        , status { parse_status(json["status"]) }
        , visibility { parse_visibility(json["visibility"]) }
    {};

    friend QDebug & operator<<(QDebug & d, ToDoDto const & dto) {
        // TODO: Improve this
        QString statStr;
        if (dto.status.has_value()) {
            statStr = ToDoDto::status_to_string(dto.status.value());
        } else {
            statStr = "none";
        }

        QString visStr;
        if (dto.visibility.has_value()) {
            visStr = ToDoDto::visibility_to_string(dto.visibility.value());
        } else {
            visStr = "none";
        }

        d << "id: " << dto.id << "\n"
            << "userId: " << dto.userId << "\n"
            << "title: " << dto.title << "\n"
            << "description: " << dto.description << "\n"
            << "status: " << statStr << "\n"
            << "visibility: " << visStr;
        return d;
    };
};

#endif // TODODTO_H
