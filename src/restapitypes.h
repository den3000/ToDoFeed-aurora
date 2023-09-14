#ifndef RESTAPITYPES_H
#define RESTAPITYPES_H

#include "easy_import.h"

#include <QFutureWatcher>

enum class RestError { NetworkError, SslError, NullResponse, EmptyJsonResponse, JsonParsingError };

template <typename Result>
using RestResult = variant<Result, RestError>;

template <typename Result>
using RestResultWatcher = QFutureWatcher<RestResult<Result>>;

enum class RestReqType{ GET, POST };

struct RestApiRequest {
    virtual QString endpoint() const = 0;
    virtual RestReqType reqType() const = 0;
    virtual void fill(QJsonObject & jo) const = 0;
};

struct RestApiResponse {
    virtual bool parse(QJsonDocument const & jd) = 0;
};

#endif // RESTAPITYPES_H
