#include "Constraints.h"

void main()
{
	try
	{
		setlocale(LC_ALL, "Rus");
		Set set(3);
		cout << set;
		Point p1(0,1), p2(1,1);
		if(set.Belongs(p1))
			cout << "Точка (0,1) принадлежит множеству" << endl;
		else
			cout<< "Точка (0,1) не принадлежит множеству" << endl;
		if(set.IsOnBound(p1))
			cout << "Точка (0,1) лежит на границе множества" << endl;
		else
			cout << "Точка (0,1) не лежит на границе множества" << endl;
		if(set.Belongs(p2))
			cout << "Точка (1,1) принадлежит множеству" << endl;
		else
			cout<< "Точка (1,1) не принадлежит множеству" << endl;
		if(set.IsOnBound(p2))
			cout << "Точка (1,1) лежит на границе множества" << endl;
		else
			cout << "Точка (1,1) не лежит на границе множества" << endl;
	}
	catch (const char *error)
	{
		cout << error << endl;
	}

}