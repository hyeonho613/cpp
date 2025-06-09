#ifndef HUMAN_H
#define HUMAN_H

#include "Monster.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

enum Direction { Left = 68, Right = 67, Up = 65, Down = 66 }; // Linux arrow key codes

class Human : public Monster {
public:
    Human(string n = "Human", string i = "H ", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    ~Human() { cout << " [Human   ]"; }
};

class Tuman : public Human {
public:
    Tuman(string n = "Tuman", string i = "T ", int px = 0, int py = 0)
        : Human(n, i, px, py) {}
    ~Tuman() { cout << " [Tuman   ]"; }

    void move(int** map, int maxx, int maxy) {
        // Human's move is no longer used
    }

    void moveHuman(int** map, int maxx, int maxy, unsigned char ch) {
        if (ch == Left || ch == 'a') x--;
        else if (ch == Right || ch == 'd') x++;
        else if (ch == Up || ch == 'w') y--;
        else if (ch == Down || ch == 's') y++;
        else return;
        clip(maxx, maxy);
        eat(map);
    }
};

#endif // HUMAN_H