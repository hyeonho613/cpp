#include "MonsterWorld.h"
#include "Human.h"
#include "RankingBoard.h"
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>

using namespace std;

void getPassword(string& passwd) {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char str[80];
    int i = 0;
    cout << "Enter admin password: ";
    while (true) {
        str[i] = getchar();
        if (str[i] == '\n') {
            str[i] = '\0';
            passwd = str;
            cout << "\n";
            break;
        }
        putchar('*');
        i++;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main()
{
    RankingBoard rank;
    try {
        rank.load("MonsterWorld.rnk");
    }
    catch (FileException e) {
        string passwd, correct = "123456";
        getPassword(passwd);
        if (passwd != correct) {
            cout << "Incorrect password. Program terminated.\n\n";
            return 1;
        }
    }
    rank.print("[Ranking Board]");

    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Zombie("Zombie1", "Z ", rand() % w, rand() % h));
    game.add(new Vampire("Vampire1", "V ", rand() % w, rand() % h));
    game.add(new KGhost("Ghost1", "G ", rand() % w, rand() % h));
    game.add(new Jiangshi("Jiangshi1", "J ", rand() % w, rand() % h, true));
    game.add(new Jiangshi("Jiangshi2", "J ", rand() % w, rand() % h, false));
    game.add(new Tuman("LeftPlayer", "L ", rand() % w, rand() % h));
    game.add(new Tuman("RightPlayer", "R ", rand() % w, rand() % h));

    game.play(500, 100);
    printf("------Game Over-------------------\n");

    Tuman* human = dynamic_cast<Tuman*>(game.getMonster(game.getNMon() - 1));
    if (human && game.getNMove() > 0) {
        rank.add(human->getNItem(), (double)human->getNItem() / game.getNMove());
    }
    rank.print("[Updated Ranking Board]");

    try {
        rank.store("MonsterWorld.rnk");
    }
    catch (FileException e) {
        string passwd, correct = "123456";
        getPassword(passwd);
        if (passwd != correct) {
            cout << "Incorrect password. Program terminated.\n\n";
            return 1;
        }
        string filename;
        cout << "Enter the filename to save the ranking: ";
        cin >> filename;
        try {
            rank.store(filename);
            cout << "Ranking saved to " << filename << ".\n";
        }
        catch (FileException e2) {
            cout << "Failed to save to " << filename << ".\n";
            return 1;
        }
    }

    return 0;
}