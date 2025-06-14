#include <vector>

#include "structs.h"

void showMenu();

void clearScreen();

void pause();

std::string base64Encode(const std::string& in);

std::string base64Decode(const std::string& in);

std::string xorCrypt(const std::string& data);

void saveLogin(const Login& login);

std::vector<Login> readLogins();

void displayLogins();

void createLogin();

void removeLogin();

std::string generatePass(Password password);

void password();
