#include <iostream>
using namespace std;

class Point
{
private:
    int xpos, ypos;
public:
    void Init(int x, int y)
    {
        xpos = x;
        ypos = y;
    }
    void ShowPointInfo() const
    {
        cout << '[' << xpos << ", " << ypos << ']' << endl;
    }
};

class Circle
{
private:
    Point center;
    int radius;
public:
    void Init(const Point &_center, const int &_radius)
    {
        center = _center;
        radius = _radius;
    }
    void ShowCircleInfo() const
    {
        cout << "radius: " << radius << endl;
        center.ShowPointInfo();
    }
};

class Ring
{
private:
    Circle uno;
    Circle dos;
    Point uno_p;
    Point dos_p;
public:
    void Init(int uno_x, int uno_y, int uno_rad, int dos_x, int dos_y, int dos_rad)
    {
        uno_p.Init(uno_x, uno_y); // uno_p, dos_p는 Point 클래스로 선언된 멤버변수이다. Point 클래스의 멤버변수를 초기화하거나 값을 대입하려면 Init 함수를 통해 진행하여야 한다.
        dos_p.Init(dos_x, dos_y);

        uno.Init(uno_p, uno_rad); // Circle 클래스의 Init 함수가 첫번째 매개변수를 Point 자료형으로 받기 때문에 Point 형식의 매개변수를 넘겨 주어야 한다.
        dos.Init(dos_p, dos_rad);
    }
    void ShowRingInfo() const
    {
        cout << "Inner Circle Info..." << endl;
        uno.ShowCircleInfo();
        cout << "Outer Circle Info..." << endl;
        dos.ShowCircleInfo();
    }
};

int main(void)
{
    Ring ring;
    ring.Init(1, 1, 4, 2, 2, 9);
    ring.ShowRingInfo();

    return 0;
}