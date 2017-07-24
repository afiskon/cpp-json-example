/* vim: set ai et ts=4 sw=4: */

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include <cstdint>
#include <iostream>
#include <sstream>

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

    rapidjson::Document toJSON() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        doc.SetArray()
            .PushBack(_year, allocator)
            .PushBack(_month, allocator)
            .PushBack(_day, allocator);
        return doc;
    }

private:
    uint16_t _year;
    uint8_t _month;
    uint8_t _day;
};

class User {
public:
    User(uint64_t id, const std::string& name, uint64_t phone, Date birthday)
      : _id(id)
      , _name(name)
      , _phone(phone)
      , _birthday(birthday) {
    }

    uint64_t getId() const {
        return _id;
    }
    const std::string& getName() const {
        return _name;
    }
    uint64_t getPhone() const {
        return _phone;
    }
    Date getBirthday() const {
        return _birthday;
    }

    User& setName(const std::string& name) {
        _name = name;
        return *this;
    }
    User& setPhone(uint64_t phone) {
        _phone = phone;
        return *this;
    }
    User& setBirthday(Date birthday) {
        _birthday = birthday;
        return *this;
    }

    rapidjson::Document toJSON() {
        rapidjson::Value json_val;
        rapidjson::Document doc;

        doc.SetObject();

        json_val.SetUint64(_id);
        doc.AddMember("id", json_val, doc.GetAllocator());

        json_val.SetString(_name.c_str(), doc.GetAllocator());
        doc.AddMember("name", json_val, doc.GetAllocator());

        // !!! see http://rapidjson.org/md_doc_tutorial.html#DeepCopyValue
        json_val.CopyFrom(_birthday.toJSON(), doc.GetAllocator());
        doc.AddMember("birthday", json_val, doc.GetAllocator());

        json_val.SetUint64(_phone);
        doc.AddMember("phone", json_val, doc.GetAllocator());

        return doc;
    }

private:
    uint64_t _id;
    std::string _name;
    uint64_t _phone;
    Date _birthday;
};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << "Date(year = " << date.getYear() << ", month = " << (int)date.getMonth() << ", day = " << (int)date.getDay()
       << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User(id = " << user.getId() << ", name = " << user.getName() << ", phone = " << user.getPhone()
       << ", birthday = " << user.getBirthday() << ")";
    return os;
}

Date readDate() {
    std::string line;
    uint16_t year, month, day;

    std::cout << "Year: ";
    std::getline(std::cin, line);
    std::stringstream(line) >> year;

    std::cout << "Month: ";
    std::getline(std::cin, line);
    std::stringstream(line) >> month;

    std::cout << "Day: ";
    std::getline(std::cin, line);
    std::stringstream(line) >> day;

    Date result(year, (uint8_t)month, (uint8_t)day);
    return result;
}

User readUser() {
    uint64_t id;
    uint64_t phone;
    std::string name, line;

    std::cout << "Id: ";
    std::getline(std::cin, line);
    std::stringstream(line) >> id;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Phone: ";
    std::getline(std::cin, line);
    std::stringstream(line) >> phone;

    std::cout << "--- Birthday ---" << std::endl;
    Date birthday = readDate();
    std::cout << "----------------" << std::endl;

    User result(id, name, phone, birthday);
    return result;
}

int main() {
    User user = readUser();
    std::cout << user << std::endl;

    {
        rapidjson::Document doc = user.toJSON();
        rapidjson::StringBuffer buffer;
        // rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::cout << buffer.GetString() << std::endl;
    }

    {
        rapidjson::Document doc = user.getBirthday().toJSON();
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::cout << buffer.GetString() << std::endl;
    }

    return 0;
}
