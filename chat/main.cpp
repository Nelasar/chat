#include <string>
#include <fstream>
#include "routine.cpp"
#include "Chat.h"

int main()
{   
    users.read_from_file("users.txt"); // �������� ���������� ������������� ��� ���������� ������
    std::filesystem::create_directory("C:\\ChatUsers"); // �������� ���������� ��� ����� �������� �������� ���������� � ������ �����

    std::cout << "List of users:\n";
    std::cout << users;

    system("pause");

    main_loop();

    return 0;
}