#include "Message.h"

Message::Message() {};
Message::Message(std::string author, std::string msg) : m_auth(author), message(msg) {}
Message::Message(const Message& m_other) { m_auth = m_other.m_auth; message = m_other.message; }
Message::~Message() = default;

std::string Message::get_msg() { return message; }
std::string Message::get_auth() { return m_auth; }
