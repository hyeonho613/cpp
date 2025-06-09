#ifndef MONSTER_WORLD_H
#define MONSTER_WORLD_H

#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "Matrix.h"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define MAXMONS 8

class MonsterWorld {
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(x, y); }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "O ");
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World (새로운 경기의 시작) ]");

        cerr << " Total moves = " << nMove << endl;
        cerr << " Remaining items = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            pMon[i]->print();
    }
public:
    MonsterWorld(int w, int h) : world(h,w), canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }
    ~MonsterWorld() { 
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }
    void add(Monster* m) {
        if (nMon < MAXMONS)
            pMon[nMon++] = m;
    }
    int getNMove() const { return nMove; }
    Monster* getMonster(int index) const { return pMon[index]; }
    int getNMon() const { return nMon; }
    void play(int maxwalk, int wait) {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        print();
        cerr << " Monster World starting...";
        getchar();

        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon-2; k++)
                pMon[k]->move(world.Data(), xMax, yMax);

            int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
            int ch = getchar();
            while (ch != EOF) {
                if (ch == 27) { // ESC (arrow keys)
                    int ch2 = getchar();
                    if (ch2 == '[') {
                        int ch3 = getchar();
                        if (ch3 != EOF)
                            ((Tuman*)(pMon[nMon-1]))->moveHuman(world.Data(), xMax, yMax, ch3);
                    }
                } else {
                    if (ch >= 'A' && ch <= 'Z') ch += 32;
                    ((Tuman*)(pMon[nMon-2]))->moveHuman(world.Data(), xMax, yMax, ch);
                }
                ch = getchar();
            }
            fcntl(STDIN_FILENO, F_SETFL, oldf);

            nMove++;
            print();
            if (isDone()) break;
            usleep(wait * 1000);
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
};

#endif // MONSTER_WORLD_H