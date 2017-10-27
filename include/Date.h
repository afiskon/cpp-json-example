/* vim: set ai et ts=4 sw=4: */

#pragma once
#include <stdexcept>
#include "rapidjson/document.h"

class Date {
public:
    Date(uint16_t year, uint8_t month, uint8_t day);

    static Date fromJSON(const rapidjson::Value& doc);
    rapidjson::Document toJSON();
    
    uint16_t getYear() const;
    uint8_t getMonth() const;
    uint8_t getDay() const;

    Date& setYear(uint16_t year);
    Date& setMonth(uint8_t month);
    Date& setDay(uint8_t day);

private:
    uint16_t _year;
    uint8_t _month;
    uint8_t _day;
};


std::ostream& operator<<(std::ostream& os, const Date& date);
