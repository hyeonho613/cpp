#pragma once
#include "Canvas.h"
#include <string>
#define DIM 40

class Monster {
    std::string name, icon; // 몬스터 이름과 화면 출력용 아이콘
    int x, y, nItem;       // 몬스터 위치와 아이템 개수
    int nEnergy;           // 몬스터 에너지

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int map[DIM][DIM]) {
        if (x >= 0 && x < DIM && y >= 0 && y < DIM) {
            if (map[y][x] == 1) {
                map[y][x] = 0;
                nItem++;
                nEnergy += 8; // 아이템을 먹으면 에너지 8 증가
            } else {
                nEnergy--; // 아이템을 먹지 못하면 에너지 1 감소
                if (nEnergy < 0) nEnergy = 0; // 에너지 최솟값은 0
            }
        }
    }
public:
    Monster(std::string n = "몬스터", std::string i = "*", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {
        // 생성 시 좌표 검증
        clip(DIM, DIM);
    }
    ~Monster() { std::cout << "\t" << name << icon << " 소멸되었습니다~~~\n"; }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    void move(int map[DIM][DIM], int maxx, int maxy) {
        switch (rand() % 8) {
        case 0: y--; break;
        case 1: x++; y--; break;
        case 2: x++; break;
        case 3: x++; y++; break;
        case 4: y++; break;
        case 5: x--; y++; break;
        case 6: x--; break;
        case 7: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
    }
    void print() { 
        std::cout << "\t" << name << icon << ": 아이템=" << nItem << ", 에너지=" << nEnergy << std::endl; 
    }
};