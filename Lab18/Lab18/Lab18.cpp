#include "stdafx.h"

bool PolishNotation(char*, string&);

int main()
{
    setlocale(LC_ALL, "Rus");
    char str[100];
    string result;
    cout << "Введите строку: ";
    cin.getline(str, 100);
    cout << endl;
    if (PolishNotation(str, result))
    {
        cout << "Преобразование выполнено успешно!" << endl;
        cout << "Исходная строка: " << str << endl;
        cout << "Преобразованная строка: " << result << endl;
    }
    else
        cout << "Преобразование не выполнено" << endl;
    return 0;
}
