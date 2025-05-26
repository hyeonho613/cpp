#include <iostream>

class Point
{
    protected: 
    // private:
        int x, y; // 10줄에 의해 x, y를 초기화

    public:
        Point(int xx, int yy) : x(xx), y(yy) {} // 27줄에 의해 Point 생성자가 호출됨

        virtual void draw() // 오버라이드를 위해 virtual 추가
        {
            std::cout << x << "," << y << "에 점을 그려라." << std::endl;
        }
};

// (1) Point 클래스를 상속사여 Rectangle 클래스르 정의하라.
//     가로, 세로 길이를 나타내는 width, height 멤버를 추가하라.
class Rectangle : public Point
{
    private:
        int width, height;

    public:
        // (2) 위에서 추가한 멤버 width와 height를 초기화 리스트를 사용하여 초기화하라.
        Rectangle(int xx, int yy, int w, int h) : Point(xx, yy), width(w), height(h) {} // Point 생성자를 실행

        // (3) draw() 함수를 재정의 하라.
        void draw() override
        {
            std::cout << x << "," << y << "에 가로 " << width 
              << " 세로 " << height << "인 사각형을 그려라." << std::endl; // 7줄에서 초기화된 x, y값을 호출
        }                                                               // protected 이기 때문에 접근 가능
};

int main()
{
    Point point(2, 3);
    Rectangle rectangle(4, 5, 100, 200);

    std::cout << "\nPoint 클래스의 draw() 함수 실행 결과 :" << std::endl;
    point.draw();

    std::cout << "\nRectangle 클래스의 draw() 함수 실행 결과 :" << std::endl;
    rectangle.draw();

    return 0;
}

