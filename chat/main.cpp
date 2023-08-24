#include <string>
#include <fstream>
#include "routine.cpp"
#include "Chat.h"

int main()
{   
    users.read_from_file("users.txt"); // считывем сохранённых пользователей для дальнейшей работы
    std::filesystem::create_directory("C:\\ChatUsers"); // создание директории для более удобного хранения ифнормации о личных чатах

    std::cout << "List of users:\n";
    std::cout << users;

    system("pause");

    main_loop();

    return 0;
}