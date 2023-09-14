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

    SignUpRequest(QString password,
            QString firstName,
            QString lastName,
            QString about)
        : password { move(password) }
        , firstName { move(firstName) }
        , lastName { move(lastName) }
        , about { move(about) }
    {};

    void fill(QJsonObject &jo) const override {
        jo["password"] = "qwer123";
        jo["firstName"] = "John";
        jo["lastName"] = "Doe";
        jo["about"] = "Movie Star";
    };
};

struct SignUpResponse: public RestApiResponse {
    UserDto user;
    QString token;

    // required to make it work with variant
    explicit SignUpResponse(){};

    bool parse(const QJsonDocument &jd) override {
        auto jo= jd.object();
        if (jo.isEmpty()) { return false; }

        token = jo["token"].toString();

        user = UserDto(jo);
        return true;
    }
};

#endif // SIGNUP_H
