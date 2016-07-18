#include "Constraints.h"

void main()
{
	try
	{
		setlocale(LC_ALL, "Rus");
		Set set(3);
		//cout << set;
		Point p1(0,1), p2(1,1);
		if(set.Belongs(p1))
			cout << "����� (0,1) ����������� ���������" << endl;
		else
			cout<< "����� (0,1) �� ����������� ���������" << endl;
		if(set.IsOnBound(p1))
			cout << "����� (0,1) ����� �� ������� ���������" << endl;
		else
			cout << "����� (0,1) �� ����� �� ������� ���������" << endl;
		if(set.Belongs(p2))
			cout << "����� (1,1) ����������� ���������" << endl;
		else
			cout<< "����� (1,1) �� ����������� ���������" << endl;
		if(set.IsOnBound(p2))
			cout << "����� (1,1) ����� �� ������� ���������" << endl;
		else
			cout << "����� (1,1) �� ����� �� ������� ���������" << endl;
	}
	catch (const char *error)
	{
		cout << error << endl;
	}

}