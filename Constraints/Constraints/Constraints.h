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

// класс, определяющий линейную функцию
class Line : public Function
{
	double a, b; // коэффициенты линейной функции
public:
	// конструктор линейной функции
	Line (Point = (0,0));
	// переопределение виртуальной функции
	// вычисления функции
	double Calculate(Point);
	// переопределение виртуальной функции ввода
	// параметров функции
	void Input();
	// переопределение виртуальной функции
	// вывода на печать
	void Output();
};

// класс, задающий эллиптическую функцию
class Ellipse : public Function
{
	// параметры, задающие эллиптическую функцию
	double a, b;
	double x0, y0;
public:
	// конструктор эллиптической функции
	Ellipse(double = 1, double = 1,
		double = 1, double = 1);
	// переопределение виртуальной функции
	// вычисления функции
	double Calculate(Point);
	// переопределение виртуальной функции ввода
	// параметров функции
	void Input();
	// переопределение виртуальной функции
	// вывода на печать
	void Output();
};