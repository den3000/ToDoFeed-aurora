#ifndef EASY_IMPORT_H
#define EASY_IMPORT_H

#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>
#include <optional>
#include <variant>
#include <vector>

using std::optional;
using std::make_optional;
using std::nullopt;

using std::variant;
using std::get_if;

using std::vector;

using std::move;

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
