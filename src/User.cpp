/* vim: set ai et ts=4 sw=4: */

#include <User.h>
#include <Date.h>

User::User(uint64_t id, const std::string& name, uint64_t phone, Date birthday)
  : _id(id)
  , _name(name)
  , _phone(phone)
  , _birthday(birthday) {
}

User User::fromJSON(const rapidjson::Value& doc) {
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

rapidjson::Document User::toJSON() {
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

uint64_t User::getId() const {
    return _id;
}

const std::string& User::getName() const {
    return _name;
}

uint64_t User::getPhone() const {
    return _phone;
}

Date User::getBirthday() const {
    return _birthday;
}

User& User::setName(const std::string& name) {
    _name = name;
    return *this;
}

User& User::setPhone(uint64_t phone) {
    _phone = phone;
    return *this;
}

User& User::setBirthday(Date birthday) {
    _birthday = birthday;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User(id = " << user.getId() << ", name = " << user.getName() << ", phone = " << user.getPhone()
       << ", birthday = " << user.getBirthday() << ")";
    return os;
}

