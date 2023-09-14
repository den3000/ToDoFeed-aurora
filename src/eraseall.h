#ifndef ERASEALL_H
#define ERASEALL_H

#include "restapitypes.h"
#include "userdto.h"

struct EraseAllRequest: public RestApiRequest {

    QString endpoint() const override { return "/erase_all"; };

    RestReqType reqType() const override { return RestReqType::GET; };

    void fill(QJsonObject &jo) const override {
        Q_UNUSED(jo);
    };
};

struct EraseAllResponse: public RestApiResponse {
    QString errorMsg = "";

    // required to make it work with variant
    explicit EraseAllResponse(){};

    bool parse(const QJsonDocument &jd) override {
        auto jo = jd.object();
        if (jo.contains("error")) {
            errorMsg = jo["error"].toString();
            return false;
        }
        return true;
    }

    QString const & error() const override { return errorMsg; }
};


#endif // ERASEALL_H
