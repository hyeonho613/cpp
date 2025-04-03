#include <iostream>
#include <cstdlib>
#include <ctime>

// 무작위로 0과 1을 채우는 함수
void randomMap3(int map[5][5]) 
{
    std::srand(std::time(0));  // 현재 시간을 시드로 사용
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            map[i][j] = std::rand() % 2;  // 0 또는 1
}

// 2차원 배열을 출력하는 함수
void printMap3(int map[5][5]) 
{
    std::cout << "[5 x 5 행렬]\n";
    for (int i = 0; i < 5; ++i) 
    {
        for (int j = 0; j < 5; ++j)
            std::cout << map[i][j] << " ";
        std::cout << std::endl;
    }
}

// 가로, 세로, 대각선이 모두 0 또는 모두 1인지 검사하는 함수
void checkMap3(int map[5][5]) 
{
    // 가로줄 검사
    for (int i = 0; i < 5; ++i) 
    {
        bool allZero = true, allOne = true;
        for (int j = 0; j < 5; ++j) 
        {
            if (map[i][j] != 0) allZero = false;
            if (map[i][j] != 1) allOne = false;
        }
        if (allZero || allOne) 
        {
            std::cout << "가로 " << i + 1 << "번째 줄이 모두 " << (allZero ? 0 : 1) << "입니다.\n";
        }
    }

    // 세로줄 검사
    for (int j = 0; j < 5; ++j) 
    {
        bool allZero = true, allOne = true;
        for (int i = 0; i < 5; ++i) 
        {
            if (map[i][j] != 0) allZero = false;
            if (map[i][j] != 1) allOne = false;
        }
        if (allZero || allOne) 
        {
            std::cout << "세로 " << j + 1 << "번째 줄이 모두 " << (allZero ? 0 : 1) << "입니다.\n";
        }
    }

    // 대각선 ↘ 검사
    bool diag1AllZero = true, diag1AllOne = true;
    for (int i = 0; i < 5; ++i) 
    {
        if (map[i][i] != 0) diag1AllZero = false;
        if (map[i][i] != 1) diag1AllOne = false;
    }
    if (diag1AllZero || diag1AllOne) 
    {
        std::cout << "대각선 ↘이 모두 " << (diag1AllZero ? 0 : 1) << "입니다.\n";
    }

    // 대각선 ↙ 검사
    bool diag2AllZero = true, diag2AllOne = true;
    for (int i = 0; i < 5; ++i) 
    {
        if (map[i][4 - i] != 0) diag2AllZero = false;
        if (map[i][4 - i] != 1) diag2AllOne = false;
    }
    if (diag2AllZero || diag2AllOne) 
    {
        std::cout << "대각선 ↙이 모두 " << (diag2AllZero ? 0 : 1) << "입니다.\n";
    }
}

// 메인 함수
int main() {
    int map[5][5];

    randomMap3(map);      // 무작위로 맵 생성
    printMap3(map);       // 맵 출력
    std::cout << "\n[검사 결과]\n";
    checkMap3(map);       // 검사 실행

    return 0;
}
