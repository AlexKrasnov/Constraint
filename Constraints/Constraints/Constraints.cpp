#include "Constraints.h"

Line:: Line(Point pt)
{
	a = pt.x;
	b = pt.y;
}

double Line:: Calculate (Point pt)
{
	return a * pt.x + b * pt.y;
}

void Line:: Input()
{
	cin >> a >> b;
}

void Line:: Output()
{
	cout << a << "*x + " << b << "*y";
}