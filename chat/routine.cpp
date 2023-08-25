#define NOMINMAX
#include <limits>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <filesystem>
#include "Network.cpp"
#include "Chat.h"

#define NO_USER -1 // для функции поиска , означает, что пользователь не найден


// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
static bool active = true;                                      // флаг работы приложения, если false, то работа программы завершена
static Array<User> users;                                       // массив, в котором хранятся все зарегистрированные пользователи
static User* current_user;                                      // текущий пользователь, используется для входа в чат и при
static Chat* global_chat;                                       // переменная для работы с глобальным чатом
static std::string users_path_string = "C:\\ChatUsers\\";       // путь для хранения папок пользователей


// ФУНКЦИИ ДЛЯ ЧАТОВ
// всомогательная функция работы глобального чата для функции main_menu
inline void global_chatting() {
    system("cls");
    global_chat = new Chat("global.txt");
    global_chat->load_chat();
    global_chat->print_chat();

    bool messaging = true;

    while (messaging) {
        if (global_chat->messaging(*current_user, "global.txt")) continue;

        else messaging = false;
    }
}
// вспомогательная функция работы персонального чата для функции main_menu
inline void personal_chatting(User& other) {
    system("pause");

    std::string rec_path_string = users_path_string + current_user->get_login() + "\\" + other.get_login() + ".txt";
    std::string trans_path_string = users_path_string + other.get_login() + "\\" + current_user->get_login() + ".txt";

    std::cout << rec_path_string << '\n';
    std::cout << trans_path_string << '\n';

    if (!std::filesystem::exists(users_path_string + current_user->get_login())) {
        std::filesystem::create_directory(users_path_string + current_user->get_login()); // создаём для нового пользователя свою директорию
    }
    if (!std::filesystem::exists(users_path_string + other.get_login())) {
        std::filesystem::create_directory(users_path_string + other.get_login()); // создаём для нового пользователя свою директорию
    }

    system("pause");

    Chat* personal_chat = new Chat(rec_path_string);
    bool messaging = true;

    personal_chat->load_chat();

    while (messaging) {
        if (personal_chat->messaging(*current_user, trans_path_string)) continue;
        else messaging = false;
    }
    
    delete personal_chat;
    system("pause");
}

// ФУНКЦИИ ДЛЯ РЕГИСТРАЦИИ
// вспомогательная функция, проверяет если ли уже зарегистрированный пользователь с таким логином/именем
inline bool is_already_registered(std::string login, std::string username) {
    for (int i = 0; i < users.getSize(); i++) {
        if (users[i].get_login() == login) {
            std::cout << "User with this login already exists!\n";
            return true;
        }
        else if (users[i].get_name() == username) {
            std::cout << "User with this name already exists!\n";
            return true;
        }
        else return false;
    }
    return false;
}
// функция регистрации пользователя
inline bool registration() {
    system("cls");

    std::string nu_name{};
    std::string nu_pass{};
    std::string nu_login{};
    std::string nu_pass_repeat{}; // для верификации пароля

    bool flag = true;

    do {
        std::cout << "Enter your login. You will use to enter the chat:\n";
        std::cin >> nu_login;
        std::cout << "Input your Username. Other users will see this name\n";
        std::cin >> nu_name;

    } while (flag = is_already_registered(nu_login, nu_name), flag);

    std::cout << "Enter your password. You will use it to get access to the chat:\n";
    std::cin >> nu_pass;

    std::cout << "Repeat your password:\n";

    std::cin >> nu_pass_repeat;

    while (nu_pass != nu_pass_repeat) {
        std::cout << "Passwords do not match!\nRepeat your input:\n";
        std::cin >> nu_pass_repeat;
    }
    
    std::cout << "\nYour registration info:\n";
    std::cout << "Your username: " << nu_name << '\n';
    std::cout << "Your login: " << nu_login << '\n';
    std::cout << "Your password: " << nu_pass << '\n';

    User* new_user = new User(nu_login, nu_name, nu_pass); // Создаём нового пользователя по введённым данны м
    users.pushBack(*new_user); // и добавляем его в массив зарегистрированных пользователей

    std::cout << users;
    users.write_on_file("users.txt", (*new_user)); // сразу после этого сохраняем пользователя в файле

    std::cout << "Registration completed!\n";

    std::filesystem::create_directory("C:\\ChatUsers\\" + nu_login); // создаём для нового пользователя свою директорию

    system("pause");

    delete new_user; // чистим память 
    return false;
}

// ФУНКЦИИ ДЛЯ ВХОДА В СИСТЕМУ
// вспомогательная функция поиска пользователя среди зарегистрироанных по логину
inline int find_user_by_login(std::string login) {
    for (int i = 0; i < users.getSize(); i++) {
        if (users[i].get_login() == login) {
            return i;
        }
    }
    return NO_USER;
}
// функция валидации пароля пользователя
inline bool validate_password(std::string password, int index) {
    if (users[index].get_password() == password) {
        return true;
    }
    else return false;
}
// функция входа в систему
inline bool log_in() {
    system("cls");
    std::string login{};
    std::string pass{};

    std::cout << "Please input your log in info:\n";
    std::cout << "Input login:\n";
    std::cin >> login;

    int index = find_user_by_login(login);

    if (index == NO_USER) { // проверяем, есть ли такой пользователь в "базе" Вообще
        std::cout << "There is no user with login " << login << "!\n";
        system("pause");
        return false;
    }

    std::cout << "Input password:\n";
    std::cin >> pass;

    if (validate_password(pass, index)) { // если всё сошлось, то логинимся!
        current_user = new User(users[index]);

        std::cout << "Welcome!\n";
        system("pause");
        return true;
    } 
    else { // иначе доступ запрещён
        std::cout << "Access denied!\n";
        system("pause");
        return false;
    }

    system("pause");
}
// Приветственное меню, можно зарегистрироваться, залогиниться и выйти
inline bool greetings() {
    system("cls");
    std::cout << "Hello!\n";
    std::cout << "To enter the chat (R)egister or (L)og in!\n";
    std::cout << "Q for quit\n";

    char option{};

    option = std::cin.get();

    switch (option) {
        case 'r':
        case 'R': {
            return registration();
            break;
        }
        case 'l':
        case 'L': {
            return log_in();
            break;
        }
        case 'q':
        case 'Q': {
            active = false;
            break;
        }
        default: {
            std::cout << "There is no such option!\n";
            system("pause");
            break;
        }
    }
}


#define MESSAGE_BUFFER 4096
#define PORT 7777

static char buffer[MESSAGE_BUFFER];
static char message[MESSAGE_BUFFER];
static int socket_file_descriptor;

#ifdef _WIN32
typedef int socklen_t;
#endif

static socklen_t message_size, length;
static const char* end_string = "end"; 

static WSADATA wsaData;

static struct sockaddr_in serveraddress, client;

// Главный цикл и меню 
enum MENU { // перечисление опций меню
    GLOBAL = 1,
    PERSONAL = 2,
    ONLINE = 3,
    LOGOUT = 4,
    QUIT = 5
};
// главное меню программы, доступно только после входа по логину и паролю.
inline bool main_menu() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        system("pause");
    }
    socket_file_descriptor = static_cast<int>(socket(AF_INET, SOCK_DGRAM, 0));

    if (socket_file_descriptor == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        system("pause");
#ifdef _WIN32
        WSACleanup();
#endif
        // return false;
    }

    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    // BIND SOCKET TO ADDRESS AND PORT
    if (bind(socket_file_descriptor, reinterpret_cast<struct sockaddr*>(&serveraddress),
        sizeof(serveraddress)) == -1) {
        std::cerr << "Failed  to bind socket" << std::endl;
        system("pause");
#ifdef _WIN32
        closesocket(socket_file_descriptor);
        WSACleanup();
#endif
        // return true;
    }

    int option{};

    // Текстовое меню
    system("cls");
    std::cout << "Enjoy your time!\nChoose an option: ";
    std::cout << "1 - Enter Global Chat\n";
    std::cout << "2 - Enter Personal Chat\n";
    std::cout << "3 - Enter Online Chat\n";
    std::cout << "4 - Log Out\n";
    std::cout << "5 - Quit\n";
    std::cout << "Input '\\quit' in chats to leave the chat.\n";
    std::cout << "\nInput option: ";

    std::cin >> option;

    while (true) {
        if ((!std::cin.fail() && option < GLOBAL && option > QUIT) || (std::cin.fail())) {
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            std::cin.clear();

            std::cout << "Wrong input!\nTry again:\n";
            std::cin >> option;
        }
        else break;
    }

    switch (option) {
    case GLOBAL: {
        // глобальный чат
        global_chatting();

        return true;
        break;
    }
    case PERSONAL: {
        // персональный чат
        try {
            int index = 0;
            std::cout << "Who do you want chat with? Input index.\nInput zero (0) to exit this menu.\n";

            for (int i = 0; i < users.getSize(); i++) {
                std::cout << i + 1 << ". " << users[i].get_name() << '\n';
            }

            std::cin >> index;

            while (true) {
                if ((!std::cin.fail() && index < 0 && option > users.getSize() + 1) || (std::cin.fail())) {

                    //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
                    std::cin.clear();
                    //std::cout << "Wrong input!\nTry again:\n";
                    //std::cin >> index;
                    throw bad_index();
                }
                else break;
            }


            if (!index) return true;
            else personal_chatting(users[index - 1]);

            return true;
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
            system("pause");
            break;
        }
        break;
    }
    case ONLINE: {
        std::cout << "SERVER IS LISTENING THROUGH THE PORT: " << PORT << " WITHIN A LOCAL SYSTEM" << std::endl;

        while (true) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            length = sizeof(client);
            // RECEIVE DATA FROM CLIENT
            message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer) - 1, 0,
                reinterpret_cast<struct sockaddr*>(&client), &length);

            if (message_size == -1) {
                std::cerr << "Faild to receive data from client" << std::endl;
#ifdef _WIN32
                closesocket(socket_file_descriptor);
                WSACleanup();
#else
                close(socket_file_descriptor);
#endif
                return true;
            }

            buffer[message_size] = '\0';

            // CHECK FOR TERMINATION SIGNAL
            if (strcmp(buffer, end_string) == 0) {
                std::cout << "Server is quitting" << std::endl;
#ifdef _WIN32
                closesocket(socket_file_descriptor);
                WSACleanup();
#else
                close(socket_file_descriptor);
#endif
                return true;
            }

            std::cout << buffer << std::endl;
            // REPLY TO CLIENT
            std::cout << "Enter message:" << std::endl;

            
            Message msg(current_user->get_name());
            std::cin >> msg;
            //std::string full_message = msg.get_auth() + ": " + msg.get_msg();

            strcpy(message, msg.formated_message().c_str());
            

            // std::cin.getline(message, MESSAGE_BUFFER);

            sendto(socket_file_descriptor, message, strlen(message), 0,
                reinterpret_cast<sockaddr*>(&client), sizeof(client));

            std::cout << message << std::endl;
            std::cout << "Waiting for the reply from Client . . ." << std::endl;
        }

        std::cout << "Server is quitting" << std::endl;
        system("pause");

#ifdef _WIN32
        closesocket(socket_file_descriptor);
        WSACleanup();
#else
        close(socket_file_descriptor);
#endif
        return true;
        break;
    }
    case LOGOUT: {
        // разлогиниться
        delete current_user;
        delete global_chat;
        return false;
        break;
    }
    case QUIT: {
        // выйти из программы
        active = false;
        return false;
        break;
    }
    default: {
        std::cout << "Nu such option, try again!\n";
        system("pause");
        return true;
        break;
    }
    }
}

// главный цикл программы, зависит от переменной active
inline void main_loop() {
    bool loged = false;

    while (active) {
        if (!loged) {
            loged = greetings();
        }
        else loged = main_menu();
    }
}


inline void network_chatting() {

}