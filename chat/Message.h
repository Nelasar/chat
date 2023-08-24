#pragma once
#include <string>
#include <iostream>

class Message {
private:
    std::string m_auth;
    std::string message;
public:
    Message();
    Message(std::string author, std::string msg);
    Message(const Message& m_other);
    ~Message();

    std::string get_msg();
    std::string get_auth();

    friend std::ostream& operator<<(std::ostream& os, const Message& obj) {
        os << obj.m_auth << ' ' << obj.message << '\n';

        return os;
    }
    friend std::istream& operator>> (std::istream& is, Message& obj) {
        // is >> obj.m_auth;
        std::getline(is, obj.message);

        return is;
    }
};