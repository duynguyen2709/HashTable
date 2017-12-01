#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"
#include <time.h>
#include <algorithm>
using namespace std;

void BuildHashTable(HashTable *&hashTable)
{
	string str;

	freopen("English-Vietnamese Dictionary.dat", "rt", stdin);

	while (!cin.eof())
	{
		getline(cin, str);

		auto colonPos = str.find_first_of(':');

		string eng = str.substr(0, colonPos);
		transform(eng.begin(), eng.end(), eng.begin(), ::tolower);

		string viet = str.substr(colonPos + 1);

		hashTable->Insert(eng, viet);

	}

	_fcloseall();
	cin.clear();
}

void SearchWord(char *input, char *output, HashTable *hashTable)
{
	string str;

	freopen(input, "rt", stdin);
	freopen(output, "wt", stdout);

	while (!cin.eof())
	{
		getline(cin, str);

		transform(str.begin(), str.end(), str.begin(), ::tolower);

		auto val = hashTable->Lookup(str);

		if (val != "")
			cout << val << endl;
		else cout << "KHONG TIM THAY" << endl;
	}
}

int main(int argc, char **argv)
{
	HashTable *hashTable;
	
	int M = atoi(argv[1]);

	char *input = argv[3];
	char *output = argv[4];


	if (strcmp(argv[2], "1"))
	{
		hashTable = new HashTable(M);
	}
	else if (strcmp(argv[2], "2"))
	{
		hashTable = new HashLinear(M);
	}
	else if (strcmp(argv[2], "3"))
	{
		hashTable = new HashQuadratic(M);
	}
	else if (strcmp(argv[2], "4"))
	{
		hashTable = new DoubleHash(M);
	}

	cout << "Building table...Please wait..." << endl;

	BuildHashTable(hashTable);

	cout << "Built table . Searching words..." << endl;
	SearchWord(input, output, hashTable);


	return 0;
}

