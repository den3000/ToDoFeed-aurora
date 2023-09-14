#ifndef EDITTODO_H
#define EDITTODO_H

#include "restapitypes.h"
#include "tododto.h"

struct EditToDoRequest: public RestApiRequest {

    QString id;
    QString title;
    QString description;
    ToDoDto::Status status;
    ToDoDto::Visibility visibility;

    QString endpoint() const override { return "/edit_todo"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    EditToDoRequest(QString id,
            QString title,
            QString description,
            ToDoDto::Status status,
            ToDoDto::Visibility visibility)
        : id { move(id) }
        , title { move(title) }
        , description { move(description) }
        , status { status }
        , visibility { visibility }
    {};

    void fill(QJsonObject &jo) const override {
        jo["id"] = id;
        jo["title"] = title;
        jo["description"] = description;
        jo["status"] = ToDoDto::status_to_string(status);
        jo["visibility"] = ToDoDto::visibility_to_string(visibility);
    };
};

struct EditToDoResponse: public RestApiResponse {
    ToDoDto todo;
    QString errorMsg;

    // required to make it work with variant
    explicit EditToDoResponse(){};

    bool parse(const QJsonDocument &jd) override {
        auto jo= jd.object();
        if (jo.isEmpty()) { return false; }
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }

        todo = ToDoDto(jo);
        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // EDITTODO_H
