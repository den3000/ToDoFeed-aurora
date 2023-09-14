#ifndef RESTAPITYPES_H
#define RESTAPITYPES_H

#include "easy_import.h"
#include "functional"

#include <QFutureWatcher>

enum class RestError { NetworkError, SslError, NullResponse, EmptyJsonResponse, JsonParsingError };

template <typename Result>
using RestResult = variant<Result, RestError>;

template <typename Result>
using RestResultWatcher = QFutureWatcher<RestResult<Result>>;

template <typename Result, typename OnResult, typename OnError>
void resOrErr(RestResultWatcher<Result> * watcher, QObject * obj, OnResult && onResult, OnError && onError, bool deleteLater = true) {
    obj->connect(watcher, &QFutureWatcher<void>::finished, obj, [watcher, onResult, onError, deleteLater](){
        auto result = watcher->result();
        if (const auto * pResponse = get_if<Result>(&result)) {
            onResult(pResponse);
        } else  if (const auto * pError = get_if<RestError>(&result)) {
            onError(pError);
        }

        if (deleteLater) {
            watcher->deleteLater();
        }
    });
};

enum class RestReqType{ GET, POST };

struct RestApiRequest {
    virtual QString endpoint() const = 0;
    virtual RestReqType reqType() const = 0;
    virtual void fill(QJsonObject & jo) const = 0;
};

struct RestApiResponse {
    virtual bool parse(QJsonDocument const & jd) = 0;
    virtual QString const & error() const = 0;
};

#endif // RESTAPITYPES_H
