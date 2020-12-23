#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const string PRODUCTS_FILE_NAME = "input.txt";
const int EXIT_FLAG = -1;

// структура - продукт
struct product {
	uint16_t ID;
	string NAME;
	string DATE;
	uint16_t QUANTITY;
	uint16_t PRICE;
};

// выводит на консоль доступные команды
void writeMenu() {

}

/*
	считывает продукты и возвращает набор продуктов
	входные параметры
		отсутствуют
	выходной параметр
		набор продуктов, прочитанных из файла
*/
vector<product> getProductsFromFile(string fileName) {
	vector<product> results;

	fstream file;
	file.open(fileName, ios::in);

	if (!file.is_open())
		return results;

	product t;
	while (!file.eof()) {
		file >> t.ID >> t.NAME >> t.DATE >> t.QUANTITY >> t.PRICE;
		results.push_back(t);
	}

	file.close();
	return results;
}

/*
	сохраняет набор продуктов в файл
	входные параметры
		const vector<product>& products - список продуктов для записи в файл
		products_File - название файла со списком продуктов
	выходной параметр
		отсутствует
*/
bool writeProductsToFile(const vector<product>& products, string products_File) {
	fstream file;
	file.open(products_File, ios::out);

	if (!file.is_open())
		return false;

	int i = 0;
	for (;i < products.size()-1; i++)
		file << products[i].ID << ' ' << products[i].NAME << ' ' 
		<< products[i].DATE << ' ' << products[i].QUANTITY << ' ' << products[i].PRICE << endl;

	file << products[i].ID << ' ' << products[i].NAME << ' '
		<< products[i].DATE << ' ' << products[i].QUANTITY << ' ' << products[i].PRICE;

	return true;
}

void writeProductsToConsole(const vector<product>& products) {
	cout << "LIST OF PRODUCTS: " << endl;
	for (auto t : products) {
		cout << t.ID << ' '
			<< t.NAME << ' '
			<< t.DATE << ' '
			<< t.QUANTITY << ' '
			<< t.PRICE << endl;
	}
}

/*
	находит первое слово - команду
	входной параметр
		string userCommand - строка, введенная пользователем
	выходной параметр
		string - первое слово строки userCommand
*/
string getCommand(string userCommand) {
	int i = 0; 
	while ((userCommand[i] != ' ') && (i < userCommand.length())) i++;

	return userCommand.substr(0, i);
}

/*
	выводит в консоль/файл список продуктов
	входные параметры
		const vector<product>& products - список продуктов для вывода
		const vector<string>& params - список параметров команды
		const uint16_t reqNum - номер запроса от пользователя
	выходной параметр
		отсутствует
*/
void getFullList(const vector<product>& products,
				const vector<string>& params, 
				const uint16_t reqNum) {
	if (params[0] == "-c") {
		writeProductsToConsole(products);
	}
	
	if (params[0] == "-f") {
		string fileName = "Request" + to_string(reqNum) + ".txt";
		writeProductsToFile(products, fileName);
	}
		
	return;
}

void setNewList(vector<product>& products, const vector<string>& params) {
	string pathToFile = params[0];

	// удаляем старые продукты 
	products.clear();

	// загружаем новые продукты из нового файла
	products = getProductsFromFile(pathToFile);
}


void addToList(vector<product>& products, const vector<string>& params) {
	string pathToFile = params[0];

	// получаем новые продукты из нового списка
	vector<product> newProducts = getProductsFromFile(pathToFile);

	// создаем временный список продуктов
	vector<product> result(products.size() + newProducts.size());

	int i = 0;
	// добавляем старые продукты
	for (auto p : products)
		result[i++] = p;

	// добавляем новые продукты
	for (auto p : newProducts)
		result[i++] = p;

	// сохраняем все продукты из временного списка
	products = result;
}


void addProduct(vector<product>& products, const vector<string>& params) {
	product temp;
	temp.ID = (uint16_t) stoi(params[0]);
	temp.NAME = params[1];
	temp.DATE = params[2];
	temp.QUANTITY = (uint16_t)stoi(params[3]);
	temp.PRICE = (uint16_t)stoi(params[4]);

	products.push_back(temp);
}

// DELETE PRICE 50

void deleteProducts(vector<product>& products, const vector<string>& params) {
	string field = params[0];
	string value = params[1];
	               
	vector<product> newProducts;
	
	if (field == "ID") {
		uint16_t v = stoi(value);

		for (auto i : products)
			if (i.ID != v)
				newProducts.push_back(i);
	}

	if (field == "NAME") {
		for (auto i : products)
			if (i.NAME != value)
				newProducts.push_back(i);
	}

	if (field == "DATE") {
		for (auto i : products)
			if (i.DATE != value)
				newProducts.push_back(i);
	}

	if (field == "QUANTITY") {
		uint16_t v = stoi(value);

		for (auto i : products)
			if (i.QUANTITY != v)
				newProducts.push_back(i);
	}

	if (field == "PRICE") {
		uint16_t v = stoi(value);

		for (auto i : products)
			if (i.PRICE != v)
				newProducts.push_back(i);
	}

	products = newProducts;
	return;
}

// FIND -c ALL NAME Banana

// XX.XX.XXXX - было
// XXXX.XX.XX - стало

string revDate(string date) {
	char delim = date[2];
	string result = date;

	result[0] = date[6];
	result[1] = date[7];
	result[2] = date[8];
	result[3] = date[9];

	result[4] = delim;

	result[5] = date[3];
	result[6] = date[4];

	result[7] = delim;

	result[8] = date[0];
	result[9] = date[1];
	
	return result;
}

//  1 date1 > date2
const int DATE_BIGGER = 1;
//  0 date1 = date2
const int DATE_EQUAL = 0;
// -1 date1 < date2
const int DATE_EARLIER = -1;

int cmpDate(string date1, string date2) {
	date1 = revDate(date1);
	date2 = revDate(date2);

	if (date1 < date2)
		return DATE_EARLIER;

	if (date1 == date2)
		return DATE_EQUAL;

	return DATE_BIGGER;
}

void findProducts(const vector<product>& products, const vector<string>& params, const int reqNum) {
	string mode = params[0];
	string type = params[1];
	string field = params[2];
	
	vector<product> searchResults;

	if (type == "ALL") {
		string value = params[3];

		if (field == "ID") {
			uint16_t v = stoi(value);

			for (auto i : products)
				if (i.ID == v)
					searchResults.push_back(i);
		}

		if (field == "NAME") {
			for (auto i : products)
				if (i.NAME == value)
					searchResults.push_back(i);
		}

		if (field == "DATE") {
			for (auto i : products)
				if (i.DATE == value)
					searchResults.push_back(i);
		}

		if (field == "QUANTITY") {
			uint16_t v = stoi(value);

			for (auto i : products)
				if (i.QUANTITY == v)
					searchResults.push_back(i);
		}

		if (field == "PRICE") {
			uint16_t v = stoi(value);

			for (auto i : products)
				if (i.PRICE == v)
					searchResults.push_back(i);
		}
	}

	if (type == "MIN") {
		if (field == "ID") {
			uint16_t min = products[0].ID;

			for (auto i : products)
				if (i.ID < min)
					min = i.ID;

			for (auto i : products)
				if (i.ID == min)
					searchResults.push_back(i);
		}

		if (field == "NAME") {
			string min = products[0].NAME;

			for (auto i : products)
				if (i.NAME < min)
					min = i.NAME;

			for (auto i : products)
				if (i.NAME == min)
					searchResults.push_back(i);
		}

		if (field == "DATE") {
			string min = products[0].DATE;

			for (auto i : products)
				if (cmpDate(i.DATE, min) == DATE_EARLIER)
					min = i.DATE;

			for (auto i : products)
				if (i.DATE == min)
					searchResults.push_back(i);
		}

		if (field == "QUANTITY") {
			uint16_t min = products[0].QUANTITY;

			for (auto i : products)
				if (i.QUANTITY < min)
					min = i.QUANTITY;

			for (auto i : products)
				if (i.QUANTITY == min)
					searchResults.push_back(i);
		}

		if (field == "PRICE") {
			uint16_t min = products[0].PRICE;

			for (auto i : products)
				if (i.PRICE < min)
					min = i.PRICE;

			for (auto i : products)
				if (i.PRICE == min)
					searchResults.push_back(i);
		}
	}

	if (mode == "-c") {
		writeProductsToConsole(searchResults);
	}
	else {
		string fileName = "Request" + to_string(reqNum) + ".txt";
		writeProductsToFile(searchResults, fileName);
	}

}

// GET_BAD_PRODUCTS -c 23.12.2020

void getBadProducts(const vector<product>& products, const vector<string>& params, const int reqNum) {
	string mode = params[0];
	string date = params[1];

	vector<product> searchResults;
	
	/*
		TO DO!
	*/

	if (mode == "-c") {
		writeProductsToConsole(searchResults);
	}
	else {
		string fileName = "Request" + to_string(reqNum) + ".txt";
		writeProductsToFile(searchResults, fileName);
	}
}

/*
	находит и выполняет команду command с параметрами params в рамках запроса reqNum
	входные параметры
		const vector<product>& products - список продуктов для вывода
		const vector<string>& params - список параметров команды
		const uint16_t reqNum - номер запроса от пользователя
	выходной параметр
		int - код результата выполнения команды
*/
int executeCommand(const string& command, 
	const vector<string>& params,
	const uint16_t reqNum) {
	vector<product> products = getProductsFromFile(PRODUCTS_FILE_NAME);

	if (command == "GET_FULL_LIST")
		getFullList(products, params, reqNum);

	if (command == "SET_NEW_LIST")
		setNewList(products, params);

	if (command == "ADD_TO_LIST")
		addToList(products, params);

	if (command == "ADD")
		addProduct(products, params);

	if (command == "DELETE")
		deleteProducts(products, params);

	if (command == "FIND")
		findProducts(products, params, reqNum);

	if (command == "EXIT")
		return EXIT_FLAG;

	writeProductsToFile(products, PRODUCTS_FILE_NAME);
	return true;
}

/*
	возвращает из строки все слова, кроме первого
	входные параметры
		string userCommand - строка для обработки
	выходной параметр
		vector<string> - набор слов, кроме первого
*/
vector<string> getParams(string userCommand) {
	string word;
	vector<string> words;

	uint16_t pos = 0;
	
	// ignore command in userCommand
	while ((userCommand[pos] != ' ') && (pos < userCommand.length())) pos++;
	pos++;

	while (pos < userCommand.length()) {
		word.clear();
		while ((userCommand[pos] != ' ') && (pos < userCommand.length()))
			word.push_back(userCommand[pos++]);

		pos++;
		words.push_back(word);
	}

	return words;
}

/*
	удаляет с каждого края строки пробелы
	входные параметры
		string& str - строка для обработки
	выходной параметр
		отсутствует
*/
void deleteFrontAndBackSpaces(string& str) {
	string result;
	int left = 0; 
	int right = str.length() - 1;

	while (str[left] == ' ') left++;
	while (str[right] == ' ') right--;

	result = str.substr(left, - left + right + 1);

	str = result;
}


int main() {
	string temp;

	uint8_t request = 1;

	while (true) {
		writeMenu();
		getline(cin, temp);
		cin.clear();

		deleteFrontAndBackSpaces(temp);

		string command = getCommand(temp);
		vector<string> params = getParams(temp);

		int flag = executeCommand(command, params, request);

		if (flag == EXIT_FLAG)
			break;

		request++;
	}
}
