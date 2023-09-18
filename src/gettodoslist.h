#ifndef GETTODOSLIST_H
#define GETTODOSLIST_H

#include "restapitypes.h"
#include "tododto.h"

struct GetToDosListRequest: public RestApiRequest {

    bool isOnlyMy;
    QString ownerId;

    QString endpoint() const override { return "/get_todos_list"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    GetToDosListRequest(bool isOnlyMy = true, QString ownerId = "")
        : isOnlyMy { isOnlyMy }
        , ownerId { ownerId }
    {}

    void fill(QJsonObject &jo) const override {
        jo["isOnlyMy"] = isOnlyMy;
        jo["ownerId"] = ownerId;
    };
};

struct GetToDosListResponse: public RestApiResponse {
    vector<ToDoDto> todos;
    QString errorMsg = "";

    // required to make it work with variant
    explicit GetToDosListResponse() {};

    bool parse(const QJsonDocument &jd) override {
        auto ja= jd.array();
        for(QJsonValue const & value : ja) {
            ToDoDto todo(value.toObject());
            todos.emplace_back(todo);
        }

        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // GETTODOSLIST_H
