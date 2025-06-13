#include <iostream>
#include <limits>

#include "helper.h"

int main()
{
    while (true)
    {
        showMenu();
        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << BRIGHT_RED + "Invalid input!\n" + RESET;
            pause();
            continue;
        }

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
                clearScreen();
                return 0;
            default:
                std::cout << BRIGHT_RED + "Invalid input!\n" + RESET;
                pause();
                break;
        }
    }
}
