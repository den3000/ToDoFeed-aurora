#ifndef GETALLUSERS_H
#define GETALLUSERS_H

#include "restapitypes.h"
#include "userdto.h"

struct GetAllUsersRequest: public RestApiRequest {

    QString endpoint() const override { return "/get_all_users"; };

    RestReqType reqType() const override { return RestReqType::GET; };

    void fill(QJsonObject &jo) const override {
        Q_UNUSED(jo);
    };
};

struct GetAllUsersResponse: public RestApiResponse {
    vector<UserDto> users;

    // required to make it work with variant
    explicit GetAllUsersResponse(){};

    bool parse(const QJsonDocument &jd) override {
        auto ja= jd.array();
        if (ja.isEmpty()) { return false; }

        for(QJsonValue const & value : ja) {
            UserDto user(value.toObject());
            users.emplace_back(user);
        }

        return true;
    }
};
#endif // GETALLUSERS_H
