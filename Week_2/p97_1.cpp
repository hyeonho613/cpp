#include <iostream>

int main() 
{
    std::cout << "[1]" << std::endl;
    for (int i = 1; i <= 5; i++) 
    {
        for (int j = 1; j <= i; j++)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[2]" << std::endl;
    for (int i = 5; i >= 1; i--)
    {
        for (int j = 5; j >= 6 - i; j--)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[3]" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5 - i; j++)
        {
            std::cout << "  ";
        }
        
        for (int j = i; j >= 1; j--)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[4]" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5 - i; j++)
        {
            std::cout << "  ";
        }

        for (int j = i; j >= 1; j--)
        {
            std::cout << j << " ";
        }

        for (int j = 2; j <= i; j++)
        {
            std::cout << j << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
