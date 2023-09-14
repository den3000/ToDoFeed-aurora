#ifndef GETMYTODOS_H
#define GETMYTODOS_H

#include "restapitypes.h"
#include "tododto.h"

struct GetMyToDosRequest: public RestApiRequest {

    QString endpoint() const override { return "/get_my_todos"; };

    RestReqType reqType() const override { return RestReqType::GET; };

    void fill(QJsonObject &jo) const override {
        Q_UNUSED(jo);
    };
};

struct GetMyToDosResponse: public RestApiResponse {
    vector<ToDoDto> todos;
    QString errorMsg = "";

    // required to make it work with variant
    explicit GetMyToDosResponse(){};

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

#endif // GETMYTODOS_H
