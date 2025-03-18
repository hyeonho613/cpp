#include <iostream>

void PrintNumber_1(int a)
{
    std::cout << "[1]" << std::endl;
    int thousnad = (a/1000);
    int hundred = (a/100) % 10;
    int ten = (a/10) %10;
    int one = a % 10;

    std::cout << thousnad << "천 ";
    std::cout << hundred << "백 ";
    std::cout << ten << "십 ";
    std::cout << one;
    std::cout << std::endl;
    std::cout << std::endl;
}

void PrintNumber_2(int a)
{
    std::cout << "[2]" << std::endl;
    int thousnad = (a/1000);
    int hundred = (a/100) % 10;
    int ten = (a/10) %10;
    int one = a % 10;

    if(thousnad > 0)
    {
        std::cout << thousnad << "천 ";
    }

    if(hundred > 0)
    {
        std::cout << hundred << "백 ";
    }

    if(ten > 0)
    {
        std::cout << ten << "십 ";
    }

    if(one > 0)
    {
        std::cout << one;
    }    

    std::cout << std::endl;
    std::cout << std::endl;
}

void PrintNumber_3(int a)
{
    std::cout << "[3]" << std::endl;
    int thousand = a / 1000;
    int hundred = (a / 100) % 10;
    int ten = (a / 10) % 10;
    int one = a % 10;

    if (thousand > 0)
    {
        if (thousand > 1)
        {
            std::cout << thousand;
        }
        std::cout << "천 ";
    }

    if (hundred > 0)
    {
        if (hundred > 1)
        {
            std::cout << hundred;
        }
        std::cout << "백 ";
    }

    if (ten > 0)
    {
        if (ten > 1)
        {
            std::cout << ten;
        }
        std::cout << "십 ";
    }

    if (one > 0)
    {
        std::cout << one;
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    int a;
    std::cout << "숫자를 입력하세요 :";
    std::cin >> a;
    PrintNumber_1(a);
    PrintNumber_2(a);
    PrintNumber_3(a);
    return 0;
}