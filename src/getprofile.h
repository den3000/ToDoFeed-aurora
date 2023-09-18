#ifndef GETPROFILE_H
#define GETPROFILE_H

#include "restapitypes.h"
#include "userdto.h"

struct GetProfileRequest: public RestApiRequest {
    QString endpoint() const override { return "/get_profile"; };

    RestReqType reqType() const override { return RestReqType::GET; };

    void fill(QJsonObject &) const override {};
};

struct GetProfileResponse: public RestApiResponse {
    UserDto user;
    bool isAdmin;
    QString errorMsg = "";

    // required to make it work with variant
    explicit GetProfileResponse() {};

    bool parse(const QJsonDocument &jd) override {
        auto jo = jd.object();
        if (jo.isEmpty()) { return false; }
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }
        user = UserDto(jo);
        isAdmin = jo["isAdmin"].toBool(false);
        return true;
    }

    QString const & error() const override { return errorMsg; }
};

#endif // GETPROFILE_H
