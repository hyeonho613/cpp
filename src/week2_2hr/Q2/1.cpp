#include <iostream>

void PrintNumber(int a)
{
    int thousnad = (a/1000);
    int hundred = (a/100) % 10;
    int ten = (a/10) %10;
    int one = a % 10;

    std::cout << thousnad << "천 ";
    std::cout << hundred << "백 ";
    std::cout << ten << "십 ";
    std::cout << one;
    std::cout << std::endl;
}

int main()
{
    int a;
    std::cout << "숫자를 입력하세요 :";
    std::cin >> a;
    PrintNumber(a);
    return 0;
}