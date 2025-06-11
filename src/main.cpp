#include <iostream>
#include <limits>

#include "helper.h"

int main()
{
  // Code
  while (true)
  {
    showMenu();
    int choice;
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice)
    {
      case 1:
        displayLogins();
        break;
      case 2:
        createLogin();
        break;
      case 3:
        password();
        break;
      case 4:
        std::cout << "Exiting!\n";
        return 0;
      default:
        std::cout << "Invalid!\n";
        break;
    }
  }
}
