#pragma once
#include <iostream>
#include <string>

#define MAXLINES 100

class Canvas {
    std::string line[MAXLINES]; // 화면 저장용 문자열
    int xMax, yMax;            // 캔버스 크기
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        for (int y = 0; y < yMax; y++)
            line[y] = std::string(xMax * 2, ' ');
    }
    void draw(int x, int y, std::string val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax)
            line[y].replace(x * 2, 2, val);
    }
    void clear(std::string val = ". ") { // 디폴트 인수: 점 2개
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                draw(x, y, val);
    }
    void print(const char *title = "<My Canvas>") {
        system("cls");
        std::cout << title << std::endl;
        for (int y = 0; y < yMax; y++)
            std::cout << line[y] << std::endl;
        std::cout << std::endl;
    }
};