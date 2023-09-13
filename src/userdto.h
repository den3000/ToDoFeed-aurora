#ifndef USERDTO_H
#define USERDTO_H

#include "easy_import.h"

struct UserDto
{
    QString id;
    QString firstName;
    QString lastName;
    QString about;

    // default constructor to make it work with variant
    explicit UserDto()
        : id { "" }
        , firstName { "" }
        , lastName { "" }
        , about { "" }
    {};

    explicit UserDto(QString id, QString firstName, QString lastName, QString about)
        : id { move(id) }
        , firstName { move(firstName) }
        , lastName { move(lastName) }
        , about { move(about) }
    {};

    explicit UserDto(QJsonObject const & json)
        : id { json["id"].toString() }
        , firstName { json["firstName"].toString() }
        , lastName { json["lastName"].toString() }
        , about { json["about"].toString() }
    {};

    friend QDebug & operator<<(QDebug & d, UserDto const & dto) {
        d << "id: " << dto.id << "\n"
            << "firstName: " << dto.firstName << "\n"
            << "lastName: " << dto.lastName << "\n"
            << "about: " << dto.about;
        return d;
    };
};

#endif // USERDTO_H
