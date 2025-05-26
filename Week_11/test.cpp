#include <iostream>

class Point
{
protected:
    int x, y;

public:
    Point(int xx, int yy) : x(xx), y(yy) {}

    // virtual 키워드 제거 (주석 처리)
    // virtual void draw()
    void draw()
    {
        std::cout << x << "," << y << "에 점을 그려라." << std::endl;
    }
};

class Rectangle : public Point
{
private:
    int width, height;

public:
    Rectangle(int xx, int yy, int w, int h) : Point(xx, yy), width(w), height(h) {}

    // override 키워드 제거 (주석 처리)
    // void draw() override
    void draw()
    {
        std::cout << x << "," << y << "에 가로 " << width 
                  << " 세로 " << height << "인 사각형을 그려라." << std::endl;
    }
};

int main()
{
    Point point(2, 3);
    Rectangle rectangle(4, 5, 100, 200);

    std::cout << "\nPoint 객체 직접 호출 결과:" << std::endl;
    point.draw();

    std::cout << "\nRectangle 객체 직접 호출 결과:" << std::endl;
    rectangle.draw();

    // 다형성 테스트: Point 포인터로 Rectangle 객체 호출
    std::cout << "\nPoint 포인터로 Rectangle 객체 호출 결과:" << std::endl;
    Point* p = &rectangle; // Rectangle 객체를 Point 포인터로 가리킴
    p->draw(); // virtual이 없으므로 Point::draw 호출됨

    return 0;
}