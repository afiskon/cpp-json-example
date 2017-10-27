/* vim: set ai et ts=4 sw=4: */

#include <Date.h>
#include <User.h>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>

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

    std::cout << "Original object:" << std::endl;
    std::cout << user << std::endl;

    {
        rapidjson::Document doc = user.toJSON();
        rapidjson::StringBuffer buffer;
        // rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        const std::string& str = buffer.GetString();
        std::cout << "Serialized:" << std::endl;
        std::cout << str << std::endl;

        // User decodedUser = User::fromJSON(doc);
        rapidjson::Document doc2;
        doc2.Parse(str.c_str());
        User decodedUser = User::fromJSON(doc2);

        std::cout << "Deserialized:" << std::endl;
        std::cout << decodedUser << std::endl;
    }

    return 0;
}
