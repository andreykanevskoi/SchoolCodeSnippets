/*
 *	Standart Template Library
 *  String
 *
 *  Примеры инициализации и использования класса string
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	// создание пустой строки
	string str;

	// иницализация новой строки 
	string str1 = "First string!";

	// присваивание строки
	string str2 = str1;

	// вывод длины строки
	cout << "String's length: " << str.length() << endl;
	
	// считывание до пробела / конца строки
	cin >> str;

	// считывание до переноса строки / конца строки
	getline(cin, str);

	// обращение к элементам строки
	cout << "First symbol is " << str[0] << endl;

	// проход по строке с помощью цикла
	for (char c : str) {
		cout << c << endl;
	}

	return 0;
}