#include <string>

const std::string FILE_NAME = "logins.dat";
const char XOR_KEY = 0x5A;

struct Login
{
  std::string email;
  std::string user;
  std::string pass;
};
