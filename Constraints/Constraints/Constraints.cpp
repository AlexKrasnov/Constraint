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

//-------------------------------------------------------------

Ellipse::Ellipse(double a1, double b1, double x1, double y1)
{
	if(a1 == 0 || b1 == 0)
		throw "если параметр a или b равен нулю, эллиптическую функцию определить невозможно";
	a = a1;
	b = b1;
	x0 = x1;
	y0 = y1;
}

void Ellipse::Output()
{
	cout << "(x-" << x0 << ")^2/" << a * a << "+ (y - "
		<< y0 << ")^2/" << b * b;
}

void Ellipse::Input()
{
	cin >> a >> b >> x0 >> y0;
}

double Ellipse::Calculate(Point pt)
{
	return (pt.x - x0) * (pt.x - x0)/(a * a)+
		(pt.y - y0)*(pt.y - y0) / (b * b);
}

//-------------------------------------------------------------

