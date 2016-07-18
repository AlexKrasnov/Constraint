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

double Ellipse::Calculate(Point pt)
{
	return (pt.x - x0) * (pt.x - x0)/(a * a)+
		(pt.y - y0)*(pt.y - y0) / (b * b);
}

void Ellipse::Input()
{
	cin >> a >> b >> x0 >> y0;
}

void Ellipse::Output()
{
	cout << "(x-" << x0 << ")^2/" << a * a << "+ (y - "
		<< y0 << ")^2/" << b * b;
}

//-------------------------------------------------------------

Hyperbola::Hyperbola(double a1, double b1, double x1, double y1)
{
	if(a1 == 0 || b1 == 0)
		throw "если параметр a или b равен нулю, эллиптическую функцию определить невозможно";
	a = a1;
	b = b1;
	x0 = x1;
	y0 = y1;
}

double Hyperbola::Calculate(Point pt)
{
	return (pt.x - x0) * (pt.x - x0)/(a * a) -
		(pt.y - y0)*(pt.y - y0) / (b * b);
}

void Hyperbola::Input()
{
	cin >> a >> b >> x0 >> y0;
}

void Hyperbola::Output()
{
	cout << "(x-" << x0 << ")^2/" << a * a << "- (y - "
		<< y0 << ")^2/" << b * b;
}

//-------------------------------------------------------------

Parabola:: Parabola(double _p, double _y0) : p(_p), y0(_y0) {}

double Parabola::Calculate(Point pt)
{
	return (pt.y - y0) * (pt.y - y0) - 2 * p * pt.x;
}

void Parabola::Input()
{
	cin >> p >> y0;
}

void Parabola::Output()
{
	cout << "(y-" << y0 << ")^2" << " - 2*" << p << "*x";
}

//-------------------------------------------------------------

// функция, определяющая оператор ввода ограничения
istream& operator >> (istream& in, Constraint& ob)
{
	int choice;
	// ввод типа ограничения
	while(true)
	{
		cout << "Введите вид функции: " << endl;
		cout << "Линейная - 1" << endl;
		cout << "Эллиптическая - 2" << endl;
		cout << "Гиперболическая - 3" << endl;
		cout << "Параболическая - 4" << endl;
		in >> choice;
		if(choice >= 1 && choice <= 4) break;
	}
	// создание объекта функции левой части ограничения
	// в зависимости от введенного типа
	switch(choice)
	{
	case 1: ob.function = new Line(); break;
	case 2: ob.function = new Ellipse(); break;
	case 3: ob.function = new Hyperbola(); break;
	case 4: ob.function = new Parabola(); break;
	}
	// ввод параметров создаваемой функции
	ob.function->Input();
	// ввод вида ограничения
	while(true)
	{
		cout << "Введите вид ограничения: " << endl;
		cout << "<= - 0, >= - 1, = - 2, < - 3,> - 4, <> - 5" << endl;
		in >> choice;
		if(choice >= 0 && choice <= 5) break;
	}
	ob.type = (type_inequation) choice;
	in >> ob.b; // ввод правой части
	return in;
}
// конструктор ограничения – запрашивает ввод
// ограничения с клавиатуры
Constraint::Constraint()
{
	cin >> *this;
}
// функция, переопределяющая оператор вывода ограничения
ostream& operator << (ostream& out, Constraint& ob)
{
	// вывод функции левой части ограничения
	ob.function->Output();
	// вывод знака вида ограничения
	switch(ob.type)
	{
	case le: out << "<="; break;
	case ge: out << ">="; break;
	case e: out << "="; break;
	case l: out << "<"; break;
	case g: out << ">"; break;
	case n: out << "<>"; break;
	default: throw "Неверный тип ограничения";
	}
	// вывод правой части ограничения
	out << ob.b << endl;
	return out;
}
// метод проверки выполнения ограничения для точки
bool Constraint::IsExecute(Point pt)
{
	// вычисление функции левой части ограничения
	double val = function->Calculate(pt);
	// сравнение с правой частью согласно виду ограничения
	switch(type)
	{
	case le: if (val <= b) return true; break;
	case ge: if (val >= b) return true; break;
	case e: if (val == b) return true; break;
	case l: if (val < b) return true; break;
	case g: if (val > b) return true; break;
	case n: if (val != b) return true; break;
	}
	return false;
}
// метод проверки выполнения равенства f(x,y) = b для
// ограничений видов "<=",">=","="
bool Constraint::IsOnBound(Point pt)
{
	// для ограничений видов "<",">", "<>"
	// равенство не должно выполняться
	if(type == l || type == g || type == n) return false;
	// вычисление значения функции в точке
	double val = function->Calculate(pt);
	// сравнение с правой частью на выполнение равенства
	if (val == b) return true;
	return false;
}

//-------------------------------------------------------------

// конструктор класса «Множество точек на плоскости»
// с заданным количеством ограничений
Set::Set(int n1)
{
	n = n1;
	constraints = new Constraint [n];
}
// деструктор класса «Множество точек на плоскости»
Set::~Set()
{
	delete [] constraints;
}
// метод проверки, принадлежит ли точка множеству
bool Set::Belongs(Point pt)
{
	// точка не принадлежит множеству, если не
	// выполняется хотя бы одно из ограничений,
	// определяющих множество
	for(int i = 0; i < n; i++)
		if (!constraints[i].IsExecute(pt))
			return false;
	return true;
}
// метод проверки, лежит ли точка на границе множества
bool Set::IsOnBound(Point pt)
{
	// точка лежит на границе, если выполняются все
	// ограничения и хотя бы одно из них – как равенство
	if (Belongs(pt))
		for(int i = 0; i < n; i++)
			if (constraints[i].IsOnBound(pt))
				return true;
	return false;
}
// функция вывода системы ограничений,
// определяющих множество
ostream& operator << (ostream& out, Set& set)
{
	for(int i = 0; i < set.n; i++)
		out << set.constraints[i];
	return out;
}

//------------------------------------------------------------