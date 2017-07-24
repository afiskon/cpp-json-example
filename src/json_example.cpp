/* vim: set ai et ts=4 sw=4: */

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
// #include "rapidjson/writer.h"
#include <cstdint>
#include <iostream>

class Date {
public:
    Date(uint16_t year, uint8_t month, uint8_t day)
      : _year(year)
      , _month(month)
      , _day(day) {
    }

    uint16_t getYear() const {
        return _year;
    }
    uint8_t getMonth() const {
        return _month;
    }
    uint8_t getDay() const {
        return _day;
    }

    Date& setYear(uint16_t year) {
        _year = year;
        return *this;
    }
    Date& setMonth(uint8_t month) {
        _month = month;
        return *this;
    }
    Date& setDay(uint8_t day) {
        _day = day;
        return *this;
    }

private:
    uint16_t _year;
    uint8_t _month;
    uint8_t _day;
};

class User {
public:
    User(uint32_t id, const std::string& name, uint32_t phone, Date birthday)
      : _id(id)
      , _name(name)
      , _phone(phone)
      , _birthday(birthday) {
    }

    uint32_t getId() const {
        return _id;
    }
    const std::string& getName() const {
        return _name;
    }
    uint32_t getPhone() const {
        return _phone;
    }
    Date getBirthday() const {
        return _birthday;
    }

    User& setName(const std::string& name) {
        _name = name;
        return *this;
    }
    User& setPhone(uint32_t phone) {
        _phone = phone;
        return *this;
    }
    User& setBirthday(Date birthday) {
        _birthday = birthday;
        return *this;
    }

private:
    uint32_t _id;
    std::string _name;
    uint32_t _phone;
    Date _birthday;
};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << "Date(year = " << date.getYear() << ", month = " << (int)date.getMonth() << ", day = " << (int)date.getDay()
       << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User(id = " << user.getId() << ", name = " << user.getName() << ", phone = " << user.getPhone()
       << ", birthday =  " << user.getBirthday() << ")";
    return os;
}

Date readDate() {
    uint16_t year, month, day;

    std::cout << "Year: ";
    std::cin >> year;

    std::cout << "Month: ";
    std::cin >> month;

    std::cout << "Day: ";
    std::cin >> day;

    Date result(year, (uint8_t)month, (uint8_t)day);
    return result;
}

int main() {
    Date birthday = readDate();
    std::cout << birthday << std::endl;
    return 0;
}
