/*
 *	Standart Template Library
 *  String
 *
 *  ������� ������������� � ������������� ������ string
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	// �������� ������ ������
	string str;

	// ������������ ����� ������ 
	string str1 = "First string!";

	// ������������ ������
	string str2 = str1;

	// ����� ����� ������
	cout << "String's length: " << str.length() << endl;
	
	// ���������� �� ������� / ����� ������
	cin >> str;

	// ���������� �� �������� ������ / ����� ������
	getline(cin, str);

	// ��������� � ��������� ������
	cout << "First symbol is " << str[0] << endl;

	// ������ �� ������ � ������� �����
	for (char c : str) {
		cout << c << endl;
	}

	return 0;
}