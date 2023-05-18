#pragma once
#include "Message.h"
#include "User.h"
#include "Template.h"

class Chat {
private:
    Array<Message> chat{}; // чат по сути это список сообщений, хранящихся в файле на сервере (как бы)
    std::string name{};    // имя чата - это название файла с расширением, используется только для работы с файловым вводом/выводом
public:
    Chat();
    Chat(std::string filename);

    // функции сохранения и загрузки чатов в/из файла
    void load_chat();
    void load_chat(std::string file);

    void save_chat();
    void save_chat(std::string file);
    // созранение в файл чата последнего сообщения
    void save_last_msg(Message& msg);
    
    bool messaging(User& user, std::string reciever_path); // функция переписки, если используется в глобальном чате, то сохранение чата происходит в один текстовый файл
                                                           // если чат персональный, то сохраняется две копии - для отправителя и получателя в соответствующих папках

    void print_chat();                                     // вывод чата на экран
};