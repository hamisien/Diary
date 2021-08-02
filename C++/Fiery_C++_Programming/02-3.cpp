/*
 * AUTHOR: hamisien
 * DATE: 2021.07.31.
 * TITLE: Fiery C++ 02-3
 */

#include <iostream>

using namespace std;

typedef struct __Point
{
	int xpos;
	int ypos;
} Point;

Point& PntAdder(const Point &p1, const Point &p2)
{
	Point* pnt0 = new Point;
	pnt0 -> xpos = p1.xpos + p2.xpos;
	pnt0 -> ypos = p1.ypos + p2.ypos;

	return *pnt0;
}

int main(void)
{
	Point* pnt1 = new Point;
	*pnt1 = {1, 2};
	// pnt1 -> xpos = 1;
	// pnt1 -> ypos = 2;

	Point* pnt2 = new Point;
	*pnt2 = {3, 4};
	// pnt2 -> xpos = 3;
	// pnt2 -> ypos = 4;

	const Point& result = PntAdder(*pnt1, *pnt2);

	cout << '[' << result.xpos << ", " << result.ypos << ']' << endl;

	delete pnt1, pnt2, &result;

	return 0;
}
