#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#define MAXLINES 100
using namespace std;

class Canvas {
    string line[MAXLINES];  // Screen output strings
    int xMax, yMax;        // Canvas size
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++) {
            line[y] = string(xMax * 2, ' ');
        }
    }
    void draw(int x, int y, string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax && (x * 2 + 1) < line[y].size()) {
            line[y].replace(x * 2, 2, val.substr(0, 2));
        }
    }
    void clear(string val = ". ") {      // Default: two dots
        for (int y = 0; y < yMax; y++) {
            line[y] = string(xMax * 2, ' ');
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
        }
    }
    void print(const char *title = "<Canvas>") {
        cout << "\033[2J\033[1;1H"; // Clear screen in Linux
        cout << title << endl;
        for (int y = 0; y < yMax; y++) {
            string output = line[y].substr(0, xMax * 2);
            while (output.size() < xMax * 2) output += ' ';
            cout << output << endl;
        }
        cout << endl;
    }
};

#endif // CANVAS_H