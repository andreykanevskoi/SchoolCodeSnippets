/*
 *	Standart Template Library
 *  Vector
 *  
 *  ������� ������������� � ������������� ���������� ������ vector<T>
 *
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v1;		    // ������� ������ ������ ��������� ���� int
	vector<int> v2 (10);    // ������� ������, ���������� 10 ��������� (�� ��������� = 0) ���� int
	vector<int> v3 (10, 7);	// ������� ������, ���������� 10 ��������� (������ = 7) ���� int

	int n;
	cin >> n;
	vector<int> a(n);

	// ���� n �������� ������� �� �������
	for (int i = 0; i < a.size(); i++)
		cin >> a[i];

	// ���������� � ����� ������� ������ ��������
	a.push_back(666);

	// ����� ��������� �������
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';

	// ����� ��������� ������� � ������� range-based for
	for (int i : a)
		cout << i << ' ';

	return 0;
}