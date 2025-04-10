#include <iostream>
#include <cstdlib>
#include <ctime>

void randomMap2(int map[5][5]) {
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            map[i][j] = std::rand() % 2;
}

void printMap2(int map[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            std::cout << map[i][j] << " ";
        std::cout << std::endl;
    }
}

int main() {
    int map[5][5];
    randomMap2(map);
    printMap2(map);
    return 0;
}
