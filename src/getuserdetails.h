#ifndef GETUSERDETAILS_H
#define GETUSERDETAILS_H

#include "restapitypes.h"
#include "userdto.h"

struct GetUserDetailsRequest: public RestApiRequest {

    QString userId;

    QString endpoint() const override { return "/get_user_details"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    GetUserDetailsRequest(QString const & userId)
        : userId { userId }
    {}

    void fill(QJsonObject &jo) const override {
        jo["userId"] = userId;
    };
};

struct GetUserDetailsResponse: public RestApiResponse {
    UserDto user;
    QString errorMsg = "";

    // required to make it work with variant
    explicit GetUserDetailsResponse() {};

    bool parse(const QJsonDocument &jd) override {
        auto jo = jd.object();
        if (jo.isEmpty()) { return false; }
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }
        user = UserDto(jo);
        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // GETUSERDETAILS_H
