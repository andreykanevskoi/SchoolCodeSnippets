/*
 *	Standart Template Library
 *  Vector
 *  
 *  Примеры инициализации и использования шаблонного класса vector<T>
 *
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v1;		    // создать пустой вектор элементов типа int
	vector<int> v2 (10);    // создать вектор, содержащий 10 элементов (по умолчанию = 0) типа int
	vector<int> v3 (10, 7);	// создать вектор, содержащий 10 элементов (каждый = 7) типа int

	int n;
	cin >> n;
	vector<int> a(n);

	// ввод n значений вектора из консоли
	for (int i = 0; i < a.size(); i++)
		cin >> a[i];

	// добавление в конец вектора нового элемента
	a.push_back(666);

	// вывод элементов вектора
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << ' ';

	// вывод элементов вектора с помощью range-based for
	for (int i : a)
		cout << i << ' ';

	return 0;
}