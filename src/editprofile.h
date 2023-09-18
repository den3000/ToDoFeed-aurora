#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include "restapitypes.h"
#include "userdto.h"

struct EditProfileRequest: public RestApiRequest {

    QString firstName;
    QString lastName;
    QString about;

    QString endpoint() const override { return "/edit_profile"; };

    RestReqType reqType() const override { return RestReqType::POST; };

    EditProfileRequest(QString const & firstName,
            QString const & lastName,
            QString const & about)
        : firstName { firstName }
        , lastName { lastName }
        , about { about }
    {};

    void fill(QJsonObject &jo) const override {
        jo["firstName"] = firstName;
        jo["lastName"] = lastName;
        jo["about"] = about;
    };
};

struct EditProfileResponse: public RestApiResponse {
    UserDto user;
    QString errorMsg;

    // required to make it work with variant
    explicit EditProfileResponse(){};

    bool parse(const QJsonDocument &jd) override {
        auto jo= jd.object();
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

#endif // EDITPROFILE_H
