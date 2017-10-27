/* vim: set ai et ts=4 sw=4: */

#pragma once

#include <Date.h>
#include <stdexcept>
#include "rapidjson/document.h"

class User {
public:
    User(uint64_t id, const std::string& name, uint64_t phone, Date birthday);

    static User fromJSON(const rapidjson::Value& doc);
    rapidjson::Document toJSON();
    uint64_t getId() const;
    const std::string& getName() const;
    uint64_t getPhone() const;
    Date getBirthday() const;

    User& setName(const std::string& name);
    User& setPhone(uint64_t phone);
    User& setBirthday(Date birthday);

private:
    uint64_t _id;
    std::string _name;
    uint64_t _phone;
    Date _birthday;
};


bool operator==(const User& d1, const User& d2);
bool operator!=(const User& d1, const User& d2);
std::ostream& operator<<(std::ostream& os, const User& user);
