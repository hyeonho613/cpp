#include <iostream>

void PrintNumber(int a)
{
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
}

int main()
{
    int a;
    std::cout << "숫자를 입력하세요: ";
    std::cin >> a;
    PrintNumber(a);
    return 0;
}
