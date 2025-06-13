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
 |)" << BRIGHT_RED + "   /$$$$$$$$ /$$$$$$$$ /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$   " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  | $$_____/|_____ $$ | $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$  " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  | $$           /$$/ | $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\__/  " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  | $$$$$       /$$/  | $$$$$$$/| $$$$$$$$|  $$$$$$ |  $$$$$$   " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  | $$__/      /$$/   | $$____/ | $$__  $$ \\____  $$ \\____  $$  " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  | $$        /$$/    | $$      | $$  | $$ /$$  \\ $$ /$$  \\ $$  " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  | $$$$$$$$ /$$$$$$$$| $$      | $$  | $$|  $$$$$$/|  $$$$$$/  " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |)" << BRIGHT_RED + "  |________/|________/|__/      |__/  |__/ \\______/  \\______/   " + RESET + RGB_PURPLE + BOLD
              << R"(|
 |                                                                |
 |     /\___/\                                                    |
 |    ( o   o ) Hi (Add ur name in src/include/helper.cpp line 34)|
 |    (  =^=  )                                                   |
 |    (        )                                                  |
 |    (         )                                                 |
 |    (          ))))))))                                         |
 +----------------------------------------------------------------+
)" << RESET << "\n";
    std::cout << RGB_PURPLE + BOLD << "[1] Display logins\n"
              << RESET;
    std::cout << RGB_PURPLE + BOLD << "[2] Create new login\n"
              << RESET;
    std::cout << RGB_PURPLE + BOLD << "[3] Generate secure password\n"
              << RESET;
    std::cout << RGB_PURPLE + BOLD << "[4] Exit\n"
              << RESET;
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

std::string base64Encode(const std::string& in) 
{
    std::string out;
    int val = 0, valb = -6;
    for (uint8_t c : in) 
    {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) 
        {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}

std::string base64Decode(const std::string& in) 
{
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;

    std::string out;
    int val = 0, valb = -8;
    for (uint8_t c : in) 
    {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) 
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
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

    auto encodeField = [](const std::string& field) 
    {
        return base64Encode(xorCrypt(field));
    };

    std::string encodedEntry =
        encodeField(login.name) + "|" +
        encodeField(login.email) + "|" +
        encodeField(login.user) + "|" +
        encodeField(login.pass);

    file << encodedEntry << '\n';
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
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        size_t pos3 = line.find("|", pos2 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos)
        {
            auto decodeField = [](const std::string& field) 
            {
                return xorCrypt(base64Decode(field));
            };

            Login login;
            login.name = decodeField(line.substr(0, pos1));
            login.email = decodeField(line.substr(pos1 + 1, pos2 - pos1 - 1));
            login.user = decodeField(line.substr(pos2 + 1, pos3 - pos2 - 1));
            login.pass = decodeField(line.substr(pos3 + 1));

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

        // Sort logins alphabetically by the 'name' field (login title)
        std::sort(logins.begin(), logins.end(), [](const Login& a, const Login& b) 
        {
            return a.name < b.name;
        });

        for (size_t i = 0; i < logins.size(); ++i)
        {
            const auto& login = logins[i];
            std::cout << BRIGHT_RED << login.name << RESET + "\n";
            std::cout << RGB_PURPLE + "   Email:    " + RESET + BRIGHT_RED << (login.email.empty() ? "..." : login.email) << RESET + "\n";
            std::cout << RGB_PURPLE + "   Username: " + RESET + BRIGHT_RED << (login.user.empty() ? "..." : login.user) << RESET + "\n";
            std::cout << RGB_PURPLE + "   Password: " + RESET + BRIGHT_RED << login.pass << RESET + "\n\n";
        }
    }
    pause();
}

// Create new login
void createLogin()
{
    Login login;

    clearScreen();

    std::cout << RGB_PURPLE + "[Required] Enter title: " + RESET;
    std::getline(std::cin, login.name);

    if (login.name.empty())
    {
        clearScreen();
        std::cout << BRIGHT_RED + BOLD + "Error: Title cannot be empty.\n" + RESET;
        pause();
        return;
    }

    std::cout << RGB_PURPLE + "[Optional] Enter email: " + RESET;
    std::getline(std::cin, login.email);

    std::cout << RGB_PURPLE + "[Optional] Enter username: " + RESET;
    std::getline(std::cin, login.user);

    std::cout << RGB_PURPLE + "[Required] Enter password: " + RESET;
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

std::string generatePass(Password password)
{
    std::string result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib;

    // Select the character set based on charSet
    std::string charSet;

    switch (password.charSet)
    {
    case 1: // No special characters
        charSet = lettersAndNumbers;
        break;
    case 2: // Some special characters
        charSet = lettersAndNumbersAndSpecial;
        break;
    case 3: // All special characters
        charSet = lettersAndNumbersAndSpecialPlus;
        break;
    default:
        throw std::invalid_argument("Invalid charSet value");
    }

    distrib = std::uniform_int_distribution<>(0, static_cast<int>(charSet.size()) - 1);

    for (int i = 0; i < password.length; ++i)
    {
        result += charSet[distrib(gen)];
    }
    return result;
}

void password()
{
    Password password;

    while (true)
    {
        clearScreen();
        std::cout << RGB_PURPLE + "Enter the length of the password: " + RESET;
        std::cin >> password.length;

        // Check if the input is valid
        if (std::cin.fail() || password.length <= 0 || password.length >= 1000)
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

    while (true)
    {
        clearScreen();
        std::cout << BRIGHT_RED + "[1] No special characters \n[2] Some special characters \n[3] All special characters\n" + RESET + RGB_PURPLE + "Character set: " + RESET;
        std::cin >> password.charSet;

        // Check if the input is valid
        if (std::cin.fail() || password.charSet <= 0 || password.charSet >= 4)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            clearScreen();
            std::cout << BRIGHT_RED + BOLD + "Invalid input. Please enter an integer between 1 and 3.\n" + RESET;
            pause();
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;  // Valid input, exit the loop
        }
    }

    clearScreen();
    std::cout << RGB_PURPLE + "Generated Password: \n" + RESET + BRIGHT_RED << generatePass(password) << "\n" + RESET;
    pause();
}
