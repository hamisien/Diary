/*
 * AUTHOR: hamisien
 * DATE: 2021.07.31.
 * TITLE: Fiery C++ 02-3
*/

#include <iostream>

Point& PntAdder(const Point &p1, const Point &p2)
{
	Point* pnt0 = new Point;
	pnt0 -> xpos = p1.xpos + p2.xpos;
	pnt0 -> ypos = p1.ypos + p2.ypos;
}

typedef struct __Point
{
	int xpos;
	int ypos;
} Point;

int main(void)
{
	Point* pnt1 = new Point;
	pnt1 -> xpos = 1;
	pnt1 -> ypos = 2;

	Point* pnt2 = new Point;
	pnt2 -> xpos = 3;
	pnt2 -> ypos = 4;

	Point& result = PntAdder(pnt1, pnt2);

	return 0;
}
