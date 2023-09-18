#ifndef SIGNUP_H
#define SIGNUP_H

#include "restapitypes.h"
#include "userdto.h"

struct SignUpRequest: public RestApiRequest {

    QString password;
    QString firstName;
    QString lastName;
    QString about;

    QString endpoint() const override { return "/register"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    SignUpRequest(QString const & password,
            QString const & firstName,
            QString const & lastName,
            QString const & about)
        : password { password }
        , firstName { firstName }
        , lastName { lastName }
        , about { about }
    {};

    void fill(QJsonObject &jo) const override {
        jo["password"] = password;
        jo["firstName"] = firstName;
        jo["lastName"] = lastName;
        jo["about"] = about;
    };
};

struct SignUpResponse: public RestApiResponse {
    UserDto user;
    QString token;
    QString errorMsg;

    // required to make it work with variant
    explicit SignUpResponse(){};

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

#endif // SIGNUP_H
