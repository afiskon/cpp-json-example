/* vim: set ai et ts=4 sw=4: */

#include <Date.h>

Date::Date(uint16_t year, uint8_t month, uint8_t day)
  : _year(year)
  , _month(month)
  , _day(day) {
}

Date Date::fromJSON(const rapidjson::Value& doc) {
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

rapidjson::Document Date::toJSON() {
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();
    doc.SetArray().PushBack(_year, allocator).PushBack(_month, allocator).PushBack(_day, allocator);
    return doc;
}

uint16_t Date::getYear() const {
    return _year;
}

uint8_t Date::getMonth() const {
    return _month;
}

uint8_t Date::getDay() const {
    return _day;
}

Date& Date::setYear(uint16_t year) {
    _year = year;
    return *this;
}

Date& Date::setMonth(uint8_t month) {
    _month = month;
    return *this;
}

Date& Date::setDay(uint8_t day) {
    _day = day;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << "Date(year = " << date.getYear() << ", month = " << (int)date.getMonth() << ", day = " << (int)date.getDay()
       << ")";
    return os;
}


