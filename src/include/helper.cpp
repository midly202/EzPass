#include "helper.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <random>

// Show menu
void showMenu()
{
    clearScreen();
    std::cout << "--- Login Manager ---\n";
    std::cout << "[1]. Display logins\n";
    std::cout << "[2]. Create new login\n";
    std::cout << "[3]. Generate secure password\n";
    std::cout << "[4]. Exit\n";
    std::cout << "Select an option: ";
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
  std::cout << "\nPress ENTER to continue...";
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
      std::cout << "No logins found!\n";
  }
  else
  {
    clearScreen();
    for (size_t i = 0; i < logins.size(); ++i)
    {
      const auto& login = logins[i];
      std::cout << "Login #" << (i + 1) << "\n";
      std::cout << "   Email:    "
                << (login.email.empty() ? "[none]" : login.email) << "\n";
      std::cout << "   Username: "
                << (login.user.empty() ? "[none]" : login.user) << "\n";
      std::cout << "   Password: " << login.pass << "\n";
    }
  }
  pause();
}

// Create new login
void createLogin()
{
  Login login;

  clearScreen();

  std::cout << "Enter email (optional): ";
  std::getline(std::cin, login.email);

  std::cout << "Enter username (optional): ";
  std::getline(std::cin, login.user);

  if (login.email.empty() && login.user.empty())
  {
    clearScreen();
    std::cout << "Error: Email and username cannot both be empty.\n";
    pause();
    return;
  }

  std::cout << "Enter password: ";
  std::getline(std::cin, login.pass);

  if (login.pass.empty())
  {
    clearScreen();
    std::cout << "Error: Password cannot be empty.\n";
    pause();
    return;
  }

  saveLogin(login);
  clearScreen();
  std::cout << "Login saved succesfully.\n";
  pause();
}

std::string generatePass(int length) 
{
    std::string result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, static_cast<int>(lettersAndNumbersAndSpecial.size()) - 1);

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
        std::cout << "Enter the length of the password (enter a value between 1-999): ";
        std::cin >> login.length;

        // Check if the input is valid
        if (std::cin.fail() || login.length <= 0 || login.length >= 1000) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            clearScreen();
            std::cout << "Invalid input. Please enter a positive integer.\n";
        }
        else 
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break; // Valid input, exit the loop
        }
    }

    clearScreen();
    std::cout << "Password: \n" << generatePass(login.length) << "\n";
    pause();
}