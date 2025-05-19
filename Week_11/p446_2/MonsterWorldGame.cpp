#include "MonsterWorld.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand((unsigned int)time(nullptr));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Zombie("좀비", "Z ", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어", "V ", rand() % w, rand() % h));
    game.add(new KGhost("백귀", "G ", rand() % w, rand() % h));
    game.add(new Jiangshi("가로강시", "J ", rand() % w, rand() % h, true));
    game.add(new Jiangshi("세로강시", "J ", rand() % w, rand() % h, false));
    game.add(new Smombi("스몸비", "S ", rand() % w, rand() % h));
    game.add(new Siangshi("슈퍼샹시", "X ", rand() % w, rand() % h, true));
    game.add(new SuperVampire("메가뱀파이어", "SV", rand() % w, rand() % h));

    game.play(500, 100);
    printf("------게임 종료-------------------\n");
    return 0;
}