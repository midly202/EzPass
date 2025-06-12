#include "helper.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <random>

// Show menu
void showMenu()
{
    clearScreen();
    std::cout << RGB_PURPLE + BOLD << R"(
 +----------------------------------------------------------------+
 |                                                                |
 |                                                                |
 |)" << BRIGHT_RED + "   /$$$$$$$$ /$$$$$$$$ /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$   " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  | $$_____/|_____ $$ | $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$  " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  | $$           /$$/ | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\__/  " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  | $$$$$       /$$/  | $$$$$$$/| $$$$$$$$|  $$$$$$ |  $$$$$$   " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  | $$__/      /$$/   | $$____/ | $$__  $$ \\____  $$ \\____  $$  " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  | $$        /$$/    | $$      | $$  | $$ /$$  \\ $$ /$$  \\ $$  " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  | $$$$$$$$ /$$$$$$$$| $$      | $$  | $$|  $$$$$$/|  $$$$$$/  " + RESET + RGB_PURPLE + BOLD << R"(|
 |)" << BRIGHT_RED + "  |________/|________/|__/      |__/  |__/ \\______/  \\______/   " + RESET + RGB_PURPLE + BOLD << R"(|
 |                                                                |
 |     /\___/\                                                    |
 |    ( o   o )   Hi Midly! :3                                    |
 |    (  =^=  )                                                   |
 |    (        )                                                  |
 |    (         )                                                 |
 |    (          ))))))))                                         |
 +----------------------------------------------------------------+
)" << RESET << "\n";
    std::cout << RGB_PURPLE + BOLD << "[1] Display logins\n" << RESET;
    std::cout << RGB_PURPLE + BOLD << "[2] Create new login\n" << RESET;
    std::cout << RGB_PURPLE + BOLD << "[3] Generate secure password\n" << RESET;
    std::cout << RGB_PURPLE + BOLD << "[4] Exit\n" << RESET;
    std::cout << BRIGHT_RED + BOLD << "Select an option: " << RESET;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");  // Windows only!
#else
    system("clear");  // Linux / MacOS only!
#endif
}

void pause()
{
    std::cout << RGB_PURPLE + "\nPress ENTER to continue..." + RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearScreen();
}

// Encrypt / decrypt with XOR
std::string xorCrypt(const std::string& data)
{
    std::string result = data;
    for (char& c : result)
    {
        c ^= XOR_KEY;
    }
    return result;
}

// Save encrypted login to file
void saveLogin(const Login& login)
{
    std::ofstream file(FILE_NAME, std::ios::app | std::ios::binary);
    if (!file)
    {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    std::string entry = login.email + "|" + login.user + "|" + login.pass;
    std::string encrypted = xorCrypt(entry);
    file << encrypted << '\n';
}

// Read all logins from file
std::vector<Login> readLogins()
{
    std::ifstream file(FILE_NAME, std::ios::binary);
    std::vector<Login> logins;
    if (!file) return logins;

    std::string line;
    while (std::getline(file, line))
    {
        line = xorCrypt(line);
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        if (pos1 != std::string::npos && pos2 != std::string::npos)
        {
            Login login;
            login.email = line.substr(0, pos1);
            login.user = line.substr(pos1 + 1, pos2 - pos1 - 1);
            login.pass = line.substr(pos2 + 1);
            logins.push_back(login);
        }
    }
    return logins;
}

// Display logins
void displayLogins()
{
    auto logins = readLogins();
    if (logins.empty())
    {
        clearScreen();
        std::cout << BRIGHT_RED + BOLD + "No logins found!\n" + RESET;
    }
    else
    {
        clearScreen();
        for (size_t i = 0; i < logins.size(); ++i)
        {
            const auto& login = logins[i];
            std::cout << BRIGHT_RED << "Login #" << (i + 1) << RESET + "\n";
            std::cout << RGB_PURPLE + "   Email:    " << (login.email.empty() ? "[none]" : login.email) << RESET + "\n";
            std::cout << RGB_PURPLE + "   Username: " << (login.user.empty() ? "[none]" : login.user) << RESET + "\n";
            std::cout << RGB_PURPLE + "   Password: " << login.pass << RESET + "\n";
        }
    }
    pause();
}

// Create new login
void createLogin()
{
    Login login;

    clearScreen();

    std::cout << RGB_PURPLE + "Enter email (optional): " + RESET;
    std::getline(std::cin, login.email);

    std::cout << RGB_PURPLE + "Enter username (optional): " + RESET;
    std::getline(std::cin, login.user);

    if (login.email.empty() && login.user.empty())
    {
        clearScreen();
        std::cout << BRIGHT_RED + BOLD + "Error: Email and username cannot both be empty.\n" + RESET;
        pause();
        return;
    }

    std::cout << RGB_PURPLE + "Enter password: " + RESET;
    std::getline(std::cin, login.pass);

    if (login.pass.empty())
    {
        clearScreen();
        std::cout << BRIGHT_RED + BOLD + "Error: Password cannot be empty.\n" + RESET;
        pause();
        return;
    }

    saveLogin(login);
    clearScreen();
    std::cout << RGB_PURPLE + "Login saved succesfully.\n" + RESET;
    pause();
}

std::string generatePass(int length)
{
    std::string result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(
        0, static_cast<int>(lettersAndNumbersAndSpecial.size()) - 1);

    for (int i = 0; i < length; ++i)
    {
        result += lettersAndNumbersAndSpecial[distrib(gen)];
    }
    return result;
}

void password()
{
    Login login;

    while (true)
    {
        clearScreen();
        std::cout << RGB_PURPLE + "Enter the length of the password (between 1 and 999): " + RESET;
        std::cin >> login.length;

        // Check if the input is valid
        if (std::cin.fail() || login.length <= 0 || login.length >= 1000)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            clearScreen();
            std::cout << BRIGHT_RED + BOLD + "Invalid input. Please enter an integer between 1 and 999.\n" + RESET;
            pause();
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;  // Valid input, exit the loop
        }
    }

    clearScreen();
    std::cout << RGB_PURPLE + "Generated Password: \n" + RESET + BRIGHT_RED << generatePass(login.length) << "\n" + RESET;
    pause();
}
