#include <vector>

#include "structs.h"

void showMenu();

void clearScreen();

void pause();

std::string xorCrypt(const std::string& data);

void saveLogin(const Login& login);

std::vector<Login> readLogins();

void displayLogins();

void createLogin();

std::string generatePass(int length);

void password();