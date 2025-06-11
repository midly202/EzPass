#include "helper.h"

#include <fstream>
#include <iostream>
#include <limits>

// Show menu
void showMenu()
{
  std::cout << "\n--- Login Manager ---\n";
  std::cout << "[1]. Display logins\n";
  std::cout << "[2]. Create new login\n";
  std::cout << "[3]. Exit\n";
  std::cout << "Select an option: ";
}

void pause()
{
  std::cout << "Press ENTER to continue...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  system("clear");  // linux only!
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

  std::string entry = login.email + "|" + login.user + "|" + login.pass + "\n";
  std::string encrypted = xorCrypt(entry);
  file << encrypted;
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
    std::cout << "No logins found!\n";
  }
  else
  {
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

  std::cout << "Enter email (optional): ";
  std::getline(std::cin, login.email);

  std::cout << "Enter username (optional): ";
  std::getline(std::cin, login.user);

  if (login.email.empty() && login.user.empty())
  {
    std::cout << "Error: Email and username cannot both be empty.\n";
    return;
  }

  std::cout << "Enter password: ";
  std::getline(std::cin, login.pass);

  if (login.pass.empty())
  {
    std::cout << "Error: Password cannot be empty.\n";
    return;
  }

  saveLogin(login);
  std::cout << "Login saved succesfully.\n";
  pause();
}
