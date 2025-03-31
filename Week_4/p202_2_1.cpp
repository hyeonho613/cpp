// 문제 : 5x5 크기의 2차원 배열에 0과 1을 임의로 채우는 함수를 구현하라.
// 이 코드는 C++로 작성된 프로그램으로, **5x5 크기의 랜덤한 0과 1로 이루어진 2차원 배열(map)**을 생성하고, 그걸 한 줄로 출력합니다.

#include <iostream> // std::cout 사용
#include <cstdlib>  // std::rand(), std::srand() 사용
#include <ctime>    // std::time 사용

void randomMap(int map[5][5]) 
{
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            map[i][j] = std::rand() % 2;
}

int main() {
    int map[5][5];
    randomMap(map);

    // 한 줄로 출력
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            std::cout << map[i][j];
    
    std::cout << std::endl;
    return 0;
}