#include <string>

const std::string FILE_NAME = "logins.dat";
const char XOR_KEY = 0x5A;

const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string numbers = "0123456789";
const std::string specialCharacters = "!@#$%^&*()-_=+[]{}|;:,.<>?";
const std::string lettersAndNumbersAndSpecial = letters + numbers + specialCharacters;

struct Login
{
  std::string email;
  std::string user;
  std::string pass;
  int length = 12;
};
