#include "MonsterWorld.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    Monster m("몬스터", "*", rand() % w, rand() % h);
    game.add(m);
    Monster m1("도깨비", "#", rand() % w, rand() % h);
    game.add(m1);
    Monster m2("별그대", "&", rand() % w, rand() % h);
    game.add(m2);
    Monster m3("고스트", "%", rand() % w, rand() % h);
    game.add(m3);
    game.play(500, 200);
    printf("------게임 종료-------------------\n");
    return 0;
}