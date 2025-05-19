#pragma once
#include "Monster.h"

class Zombie : public Monster {
public:
    Zombie(string n = "Zombie", string i = "Z ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Zombie() { cout << " Zombie"; }
};

class Vampire : public Monster {
public:
    Vampire(string n = "Vampire", string i = "V ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() { cout << " Vampire"; }

    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 4;
        if (dir == 0) x--;
        else if (dir == 1) x++;
        else if (dir == 2) y--;
        else y++;
        clip(maxx, maxy);
        eat(map);
    }
};

class KGhost : public Monster {
public:
    KGhost(string n = "KGhost", string i = "G ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() { cout << " KGhost"; }

    void move(int** map, int maxx, int maxy) override {
        x = rand() % maxx;
        y = rand() % maxy;
        clip(maxx, maxy);
        eat(map);
    }
};

class Jiangshi : public Monster {
protected:
    bool bHori;
public:
    Jiangshi(string n = "Jiangshi", string i = "J ", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() { cout << " Jiangshi"; }

    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;
        if (bHori) x += ((dir == 0) ? -jump : jump);
        else y += ((dir == 0) ? -jump : jump);
        clip(maxx, maxy);
        eat(map);
    }
};

class Smombi : public Monster {
public:
    Smombi(string n = "Smombi", string i = "S ", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Smombi() { cout << " Smombi"; }

    void move(int** map, int maxx, int maxy) override {
        int dir = rand() % 4;
        switch (dir) {
        case 0: x++; y--; break; // 북동
        case 1: x++; y++; break; // 남동
        case 2: x--; y++; break; // 남서
        case 3: x--; y--; break; // 북서
        }
        clip(maxx, maxy);
        eat(map);
    }
};

class Siangshi : public Jiangshi {
    int moveCount;
    static const int SWITCH_INTERVAL = 5;
public:
    Siangshi(string n = "Siangshi", string i = "X ", int x = 0, int y = 0, bool bH = true)
        : Jiangshi(n, i, x, y, bH), moveCount(0) {}
    ~Siangshi() { cout << " Siangshi"; }

    void move(int** map, int maxx, int maxy) override {
        moveCount++;
        if (moveCount >= SWITCH_INTERVAL) {
            bHori = !bHori;
            moveCount = 0;
        }
        Jiangshi::move(map, maxx, maxy);
    }
};

class SuperVampire : public Vampire {
public:
    SuperVampire(string n = "SuperVampire", string i = "SV", int x = 0, int y = 0)
        : Vampire(n, i, x, y) {}
    ~SuperVampire() { cout << " SuperVampire"; }

    void move(int** map, int maxx, int maxy) override {
        for (int i = 0; i < 2; i++) {
            Vampire::move(map, maxx, maxy);
        }
    }
};