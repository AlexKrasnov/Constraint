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
		throw "���� �������� a ��� b ����� ����, ������������� ������� ���������� ����������";
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
		throw "���� �������� a ��� b ����� ����, ������������� ������� ���������� ����������";
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

// �������, ������������ �������� ����� �����������
istream& operator >> (istream& in, Constraint& ob)
{
	int choice;
	// ���� ���� �����������
	while(true)
	{
		cout << "������� ��� �������: " << endl;
		cout << "�������� - 1" << endl;
		cout << "������������� - 2" << endl;
		cout << "��������������� - 3" << endl;
		cout << "�������������� - 4" << endl;
		in >> choice;
		if(choice >= 1 && choice <= 4) break;
	}
	// �������� ������� ������� ����� ����� �����������
	// � ����������� �� ���������� ����
	switch(choice)
	{
	case 1: ob.function = new Line(); break;
	case 2: ob.function = new Ellipse(); break;
	case 3: ob.function = new Hyperbola(); break;
	case 4: ob.function = new Parabola(); break;
	}
	// ���� ���������� ����������� �������
	ob.function->Input();
	// ���� ���� �����������
	while(true)
	{
		cout << "������� ��� �����������: " << endl;
		cout << "<= - 0, >= - 1, = - 2, < - 3,> - 4, <> - 5" << endl;
		in >> choice;
		if(choice >= 0 && choice <= 5) break;
	}
	ob.type = (type_inequation) choice;
	in >> ob.b; // ���� ������ �����
	return in;
}
// ����������� ����������� � ����������� ����
// ����������� � ����������
Constraint::Constraint()
{
	cin >> *this;
}
// �������, ���������������� �������� ������ �����������
ostream& operator << (ostream& out, Constraint& ob)
{
	// ����� ������� ����� ����� �����������
	ob.function->Output();
	// ����� ����� ���� �����������
	switch(ob.type)
	{
	case le: out << "<="; break;
	case ge: out << ">="; break;
	case e: out << "="; break;
	case l: out << "<"; break;
	case g: out << ">"; break;
	case n: out << "<>"; break;
	default: throw "�������� ��� �����������";
	}
	// ����� ������ ����� �����������
	out << ob.b << endl;
	return out;
}
// ����� �������� ���������� ����������� ��� �����
bool Constraint::IsExecute(Point pt)
{
	// ���������� ������� ����� ����� �����������
	double val = function->Calculate(pt);
	// ��������� � ������ ������ �������� ���� �����������
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
// ����� �������� ���������� ��������� f(x,y) = b ���
// ����������� ����� "<=",">=","="
bool Constraint::IsOnBound(Point pt)
{
	// ��� ����������� ����� "<",">", "<>"
	// ��������� �� ������ �����������
	if(type == l || type == g || type == n) return false;
	// ���������� �������� ������� � �����
	double val = function->Calculate(pt);
	// ��������� � ������ ������ �� ���������� ���������
	if (val == b) return true;
	return false;
}

//-------------------------------------------------------------

// ����������� ������ ���������� ����� �� ���������
// � �������� ����������� �����������
Set::Set(int n1)
{
	n = n1;
	constraints = new Constraint [n];
}
// ���������� ������ ���������� ����� �� ���������
Set::~Set()
{
	delete [] constraints;
}
// ����� ��������, ����������� �� ����� ���������
bool Set::Belongs(Point pt)
{
	// ����� �� ����������� ���������, ���� ��
	// ����������� ���� �� ���� �� �����������,
	// ������������ ���������
	for(int i = 0; i < n; i++)
		if (!constraints[i].IsExecute(pt))
			return false;
	return true;
}
// ����� ��������, ����� �� ����� �� ������� ���������
bool Set::IsOnBound(Point pt)
{
	// ����� ����� �� �������, ���� ����������� ���
	// ����������� � ���� �� ���� �� ��� � ��� ���������
	if (Belongs(pt))
		for(int i = 0; i < n; i++)
			if (constraints[i].IsOnBound(pt))
				return true;
	return false;
}
// ������� ������ ������� �����������,
// ������������ ���������
ostream& operator << (ostream& out, Set& set)
{
	for(int i = 0; i < set.n; i++)
		out << set.constraints[i];
	return out;
}

//------------------------------------------------------------