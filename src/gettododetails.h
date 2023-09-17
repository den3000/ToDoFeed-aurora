#ifndef GETTODODETAILS_H
#define GETTODODETAILS_H

#include "restapitypes.h"
#include "tododto.h"

struct GetToDoDetailsRequest: public RestApiRequest {

    QString toDoId;

    QString endpoint() const override { return "/get_todo_details"; };

    RestReqType reqType() const override { return RestReqType::GET; };

    GetToDoDetailsRequest(QString const & toDoId)
        : toDoId { toDoId }
    {}

    void fill(QJsonObject &jo) const override {
        jo["toDoId"] = toDoId;
    };
};

struct GetToDoDetailsResponse: public RestApiResponse {
    ToDoDto toDo;
    bool isEdiatabe;
    QString errorMsg = "";

    // required to make it work with variant
    explicit GetToDoDetailsResponse() {};

    bool parse(const QJsonDocument &jd) override {
        auto jo = jd.object();
        if (jo.isEmpty()) { return false; }
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }
        toDo = ToDoDto(jo);
        isEdiatabe = jo["isEditable"].toBool();
        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // GETTODODETAILS_H
