#ifndef ADDTODO_H
#define ADDTODO_H

#include "restapitypes.h"
#include "tododto.h"

struct AddToDoRequest: public RestApiRequest {

    QString title;
    QString description;
    ToDoDto::Status status;
    ToDoDto::Visibility visibility;

    QString endpoint() const override { return "/add_todo"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    AddToDoRequest(QString const & title,
            QString const & description,
            ToDoDto::Status status,
            ToDoDto::Visibility visibility)
        : title { move(title) }
        , description { move(description) }
        , status { status }
        , visibility { visibility }
    {};

    void fill(QJsonObject &jo) const override {
        jo["title"] = title;
        jo["description"] = description;
        jo["status"] = ToDoDto::status_to_string(status);
        jo["visibility"] = ToDoDto::visibility_to_string(visibility);
    };
};

struct AddToDoResponse: public RestApiResponse {
    ToDoDto toDo;
    QString errorMsg;

    // required to make it work with variant
    explicit AddToDoResponse() {};

    bool parse(const QJsonDocument &jd) override {
        auto jo= jd.object();
        if (jo.isEmpty()) { return false; }
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }

        toDo = ToDoDto(jo);
        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // ADDTODO_H
