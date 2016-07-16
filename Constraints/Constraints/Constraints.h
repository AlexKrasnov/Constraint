#include <iostream>

using namespace std;

struct Point
{
	double x, y;
	Point(double a = 0, double b = 0) :x(a), y(b) {}
};

// класс, задающий функцию в левой части ограничения
class Function
{
public:
	// чисто виртуальный метод вычисления функции
	virtual double Сalculate(Point) = 0;
	// чисто виртуальный метод ввода параметров функции
	virtual void Input() = 0;
	// чисто виртуальный метод вывода функции на печать
	virtual void Output() = 0;
};