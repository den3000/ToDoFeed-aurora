#ifndef LOGIN_H
#define LOGIN_H

#include "restapitypes.h"
#include "userdto.h"

struct LogInRequest: public RestApiRequest {

    QString password;

    QString endpoint() const override { return "/login"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    LogInRequest(QString const & password)
        : password { password }
    {};

    void fill(QJsonObject &jo) const override {
        jo["password"] = password;
    };
};

struct LogInResponse: public RestApiResponse {
    UserDto user;
    QString token;
    QString errorMsg;

    // required to make it work with variant
    explicit LogInResponse(){};

    bool parse(const QJsonDocument &jd) override {
        auto jo= jd.object();
        if (jo.isEmpty()) { return false; }
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }

        token = jo["token"].toString();
        user = UserDto(jo);
        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // LOGIN_H
