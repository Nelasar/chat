#pragma once
#include <string>
#include <iostream>

class User {
private:
    std::string name{};
    std::string password{};
    std::string login{};
public:
    User();
    User(std::string u_log, std::string u_pass);
    User(std::string u_log, std::string u_name, std::string u_pass);
    User(const User& u_other);
    ~User();

    std::string get_name();
    std::string get_login();
    std::string get_password();

    friend std::ostream& operator<<(std::ostream& out, const User& obj) {
        out << obj.login << ' ' << obj.name << ' ' << obj.password << '\n';

        return out;
    }
    friend std::istream& operator>>(std::istream& in, User& obj) {
        in >> obj.login;
        in >> obj.name;
        in >> obj.password;

        return in;
    }
};