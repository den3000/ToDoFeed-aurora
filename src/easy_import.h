#ifndef EASY_IMPORT_H
#define EASY_IMPORT_H

#include <QDebug>

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <vector>

#include <optional>
#include <variant>
#include <memory>

using std::vector;

using std::optional;
using std::make_optional;
using std::nullopt;

using std::variant;
using std::get_if;

using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::unique_ptr;
using std::make_unique;

using std::move;
using std::forward;
using std::enable_if_t;
using std::is_base_of;

template <typename  T>
std::ostream & operator<<(std::ostream & os, optional<T> const & opt) {
    if (opt) {
        os << "optional<" << typeid (T).name() << "> " << opt.value();
    } else {
        os << "optional<" << typeid (T).name() << "> " << "no value";
    }
    return os;
}

template <typename  T>
QDebug & operator<<(QDebug & os, optional<T> const & opt) {
    if (opt) {
        os << "optional" << typeid (T).name() << opt.value();
    } else {
        os << "optional" << typeid (T).name() << "no value";
    }
    return os;
}

template <typename R, typename Provider>
constexpr optional<R>
parse_optional(QJsonValue && value, Provider && provider) {
    if (!value.isNull()){
        return make_optional<R>(provider(move(value)));
    } else {
        return nullopt;
    }
}

//template <typename T, typename Predicate, typename R, typename Provider>
//constexpr optional<R>
//parse_optional(T && value, Predicate && predicate, Provider && provider) {
//    if (predicate(value)){
//        return make_optional<R>(provider(move(value)));
//    } else {
//        return nullopt;
//    }
//}

#endif // EASY_IMPORT_H
