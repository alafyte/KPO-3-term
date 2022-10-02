#include "stdafx.h"


int main() 
{
	long l;
	int c;
	char str[150];

	cout << "long: ";
	cin >> l;
	cout << "\nunsigned char: ";
	cin >> c;
	cout << "string: ";
	cin.ignore();
	cin.getline(str, 150);


	Serealizer serealizer(l, c, str);
	serealizer.SerealizeData();
	system("pause");
}