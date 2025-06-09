#pragma once
#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;
#define NUM_MVP 5

struct PlayInfo {
    string name;
    int nItem;
    double itemPerMove;
    PlayInfo(string na = "Ghost", int ni = 0, double ipm = 0.0)
        : name(na), nItem(ni), itemPerMove(ipm) {}
};

class RankingBoard {
    PlayInfo MVP[NUM_MVP];
    int nMVP = NUM_MVP;
public:
    void load(string filename) {
        ifstream is;
        is.open(filename);
        if (!is)
            throw(FileException(filename, true));
        for (int i = 0; i < nMVP; i++)
            is >> MVP[i].nItem >> MVP[i].name >> MVP[i].itemPerMove;
        is.close();
    }
    void store(string filename) {
        ofstream os;
        os.open(filename);
        if (!os)
            throw(FileException(filename, false));
        for (int i = 0; i < nMVP; i++)
            os << MVP[i].nItem << " " << MVP[i].name << " "
               << MVP[i].itemPerMove << "\n";
        os.close();
    }
    void print(string title = "Ranking Board") {
        cout << endl << title << endl;
        for (int i = 0; i < nMVP; i++)
            cout << "[" << i + 1 << "] " << MVP[i].name << "\t"
                 << MVP[i].nItem << " " << MVP[i].itemPerMove << "\n";
        cout << "Press Enter to continue: ";
        getchar();
        cout << endl;
    }
    int add(int nItem, double ipm) {
        if (nItem <= MVP[nMVP - 1].nItem) return 0;

        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nItem <= MVP[pos - 1].nItem) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nItem = nItem;
        MVP[pos].itemPerMove = ipm;
        cout << "Enter name for rank " << pos + 1 << ": ";
        cin >> MVP[pos].name;
        return pos + 1;
    }
};