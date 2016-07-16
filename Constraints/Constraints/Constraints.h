#include <iostream>

using namespace std;

struct Point
{
	double x, y;
	Point(double a = 0, double b = 0) :x(a), y(b) {}
};

// �����, �������� ������� � ����� ����� �����������
class Function
{
public:
	// ����� ����������� ����� ���������� �������
	virtual double �alculate(Point) = 0;
	// ����� ����������� ����� ����� ���������� �������
	virtual void Input() = 0;
	// ����� ����������� ����� ������ ������� �� ������
	virtual void Output() = 0;
};