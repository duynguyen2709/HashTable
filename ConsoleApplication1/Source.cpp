#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Header.h"
#include "Header.h"
#include <time.h>
#include <algorithm>
using namespace std;

#define MAX 101
int main(int argc, char **argv)
{
	auto start = clock();
	//HashTable * hashTable = new HashTable(MAX);
	//HashLinear * hashTable = new HashLinear(MAX);
	//HashQuadratic * hashTable = new HashQuadratic(MAX);
	DoubleHash * hashTable = new DoubleHash(MAX);
	string str;
	long count = 0;
	freopen("English-Vietnamese Dictionary.dat", "rt", stdin);
	//freopen("Output.txt", "rt", stdin);
	while (!cin.eof())
	{
		getline(cin, str);
		auto colonPos = str.find_first_of(':');
		string eng = str.substr(0, colonPos);
		string viet = str.substr(colonPos + 1);
		hashTable->Insert(eng, viet);
		count++;
	}

	auto end = clock();
	auto time = (end - start)*1.0 / 1000;
	cout << time << endl;
	cout << count << endl;

	_fcloseall();
	cin.clear();

	cout << hashTable->size << endl;

	freopen("Input.txt", "rt", stdin);
	while (!cin.eof())
	{
	getline(cin, str);
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	auto val = hashTable->Lookup(str);
	if (val != "")
	cout << val << endl;
	else cout << "KHONG TIM THAY" << endl;
	}

	return 0;
}