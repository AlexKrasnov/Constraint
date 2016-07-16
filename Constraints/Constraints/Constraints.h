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
	virtual double Calculate (Point) = 0;
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

// класс, задающий гиперболическую функцию
class Hyperbola : public Function
{
	// параметры, задающие гиперболическую функцию
	double a, b;
	double x0, y0;
public:
	// конструктор гиперболической функции
	Hyperbola(double = 1, double = 1,
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

// класс, задающий параболическую функцию
class Parabola: public Function
{
	// параметры, задающие параболическую функцию
	double p;
	double y0;
public:
	// конструктор параболической функции
	Parabola(double = 1, double = 1);
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

// перечисление для определения типа ограничения
// le – <=, ge – >=, e – =, l – <, g – >, n – <>
typedef enum {le, ge, e, l, g, n} type_inequation;

// класс, определяющий ограничение
class Constraint
{
	Function* function; // указатель на объект функции в левой части ограничения
	double b; // правая часть
	type_inequation type; // тип ограничения
public:
	Constraint(); // конструктор класса
	bool IsExecute(Point); // метод проверки выполнения ограничения
	bool IsOnBound(Point); // метод проверки выполнения равенства
	// f(x,y) = b для ограничений типа "<=", ">=", "="
	// дружественные функции ввода, вывода
	friend ostream& operator << (ostream&, Constraint&);
	friend istream& operator >> (istream&, Constraint&);
};

