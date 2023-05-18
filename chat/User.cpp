#include "User.h"

User::User() {};
User::User(std::string u_log, std::string u_pass) : login(u_log), password(u_pass) {}
User::User(std::string u_log, std::string u_name, std::string u_pass) : login(u_log), password(u_pass), name(u_name) {}
User::User(const User& u_other) {
    name = u_other.name;
    password = u_other.password;
    login = u_other.password;
}
User::~User() = default;

std::string User::get_name() { return name; }
std::string User::get_login() { return login; }
std::string User::get_password() { return password; }