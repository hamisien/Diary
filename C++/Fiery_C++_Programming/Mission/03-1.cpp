#include <iostream>

using namespace std;

struct Point
{
    int xpos;
    int ypos;

    void MovePos(int x, int y);
    void AddPoint(const Point &pos);
    void ShowPosition();
};

int main(void)
{
    Point pos1={12, 4};
    Point pos2={20, 30};
    
    pos1.MovePos(-7, 10);
    pos1.ShowPosition(); // [5, 14] 출력

    pos1.AddPoint(pos2);
    pos1.ShowPosition(); // [25, 44] 출력

    return 0;
}

void Point::MovePos(int x, int y)
{
    xpos += x;
    ypos += y;
}

void Point::AddPoint(const Point &pos)
{
    xpos += pos.xpos;
    ypos += pos.ypos;
}

void Point::ShowPosition()
{
    cout << '[' << xpos << ", " << ypos << ']' << endl;
}