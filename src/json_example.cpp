/* vim: set ai et ts=4 sw=4: */

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Date {
public:
    Date(uint16_t year, uint8_t month, uint8_t day)
      : _year(year)
      , _month(month)
      , _day(day) {
    }

    static Date fromJSON(const rapidjson::Value& doc) {
        if(!doc.IsArray())
            throw std::runtime_error("Date::fromJSON - document is not an array");

        if(doc.Size() != 3)
            throw std::runtime_error("Date::fromJSON - wrong array size");

        uint16_t year = doc[0].GetInt();
        uint8_t month = doc[1].GetInt();
        uint8_t day = doc[2].GetInt();

        Date result(year, month, day);
        return result;
    }

    rapidjson::Document toJSON() {
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();
        doc.SetArray().PushBack(_year, allocator).PushBack(_month, allocator).PushBack(_day, allocator);
        return doc;
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
    User(uint64_t id, const std::string& name, uint64_t phone, Date birthday)
      : _id(id)
      , _name(name)
      , _phone(phone)
      , _birthday(birthday) {
    }

    static User fromJSON(const rapidjson::Value& doc) {
        if(!doc.IsObject())
            throw std::runtime_error("User::fromJSON() - document should be an object");

        static const char* members[] = { "id", "name", "phone", "birthday" };
        for(size_t i = 0; i < sizeof(members) / sizeof(members[0]); i++) {
            if(!doc.HasMember(members[i]))
                throw std::runtime_error("User::fromJSON() - invalid JSON, missing fields");
        }

        if(!doc["id"].IsNumber())
            throw std::runtime_error("User::fromJSON() - invalid JSON, `id` should be an integer");

        if(!doc["name"].IsString())
            throw std::runtime_error("User::fromJSON() - invalid JSON, `name` should be a string");

        if(!doc["phone"].IsNumber())
            throw std::runtime_error("User::fromJSON() - invalid JSON, `phone` should be an integer");

        if(!doc["birthday"].IsArray())
            throw std::runtime_error("User::fromJSON() - invalid JSON, `birthday` should be an array");

        uint64_t id = doc["id"].GetUint64();
        std::string name = doc["name"].GetString();
        uint64_t phone = doc["phone"].GetUint64();
        Date birthday = Date::fromJSON(doc["birthday"]);

        User result(id, name, phone, birthday);
        return result;
    }

    rapidjson::Document toJSON() {
        rapidjson::Value json_val;
        rapidjson::Document doc;
        auto& allocator = doc.GetAllocator();

        doc.SetObject();

        json_val.SetUint64(_id);
        doc.AddMember("id", json_val, allocator);

        json_val.SetString(_name.c_str(), allocator);
        doc.AddMember("name", json_val, allocator);

        // see http://rapidjson.org/md_doc_tutorial.html#DeepCopyValue
        json_val.CopyFrom(_birthday.toJSON(), allocator);
        doc.AddMember("birthday", json_val, allocator);

        json_val.SetUint64(_phone);
        doc.AddMember("phone", json_val, allocator);

        return doc;
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

        User decodedUser = User::fromJSON(doc);
        std::cout << decodedUser << std::endl;
    }

    return 0;
}
