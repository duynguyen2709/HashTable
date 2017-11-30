#include "Header.h"





HashNode* HashTable::resize()
{
	const int oldSize = maxSize;
	maxSize = maxSize * 12 + 1;


	HashNode *temp = new HashNode[oldSize]();
	for (int i = 0; i < oldSize; i++)
		temp[i] = arr[i];

	HashNode x;
	arr = new HashNode[maxSize]();
	for (int i = 0; i < oldSize; i++)
	{
		if (temp[i].key != "" && temp[i].value != "")
		{
			Insert(temp[i].key, temp[i].value);
		}
		else arr[i] = x;
	}

	return arr;
}
HashTable::HashTable(int M)
{
	maxSize = M;
	size = 0;
	data = new HashNode*[maxSize];

	for (int i = 0; i < maxSize; i++)
		data[i] = NULL;


}

HashTable::~HashTable()
{
	for (int i = 0; i < maxSize; i++)
	{
		if (data[i] != NULL)
		{
			for (HashNode *x = data[i]; x != NULL;)
			{
				HashNode *y = x;
				x = x->next;
				delete y;
			}
		}
	}
	delete[]data;
}



unsigned int HashTable::hash(string key, int M)
{
	unsigned int result = 0;
	unsigned int length = key.length();

	for (int i = 0; i < length; i++)
	{
		int c = (int)((char)key[i]);
		int temp = (int)(c * pow((float)128, (float)(length - i - 1))) % M;
		result += temp;
	}
	result %= M;
	return  result;
}

void HashTable::Insert(string key, string value)
{
	int pos = hash(key, maxSize);
	HashNode *temp = new HashNode(key, value);
	if (data[pos] == NULL)
	{
		data[pos] = temp;
	}
	else
	{
		temp->next = data[pos];
		data[pos] = temp;
	}

}

string HashTable::Lookup(string key)
{
	int pos = hash(key, maxSize);
	for (auto val = data[pos]; val != NULL; val = val->next)
	{
		if (val->key == key)
			return val->value;
	}
	return "";
}

HashLinear::HashLinear(int M) : HashTable()
{
	arr = new HashNode[M]();
	size = 0;
	maxSize = M;
}

void HashLinear::Insert(string key, string value)
{
	int pos = hash(key, maxSize);

	while (arr[pos].key != "" && arr[pos].value != "")
	{
		pos++;
		pos %= maxSize;
	}

	HashNode x(key, value);
	arr[pos] = x;
	++size;

	if (size*1.0f / maxSize >= 0.75)
	{
		size = 0;
		resize();
	}

}

string HashLinear::Lookup(string key)
{
	int pos = hash(key, maxSize);

	while (arr[pos].key != "" && arr[pos].value != "")
	{
		if (arr[pos].key == key)
			return arr[pos].value;
		pos++;
		pos %= maxSize;
	}

	return "";
}


HashQuadratic::HashQuadratic(int M) : HashTable()
{
	arr = new HashNode[M]();
	size = 0;
	maxSize = M;
}

void HashQuadratic::Insert(string key, string value)
{
	int pos = hash(key, maxSize);
	int i = 1;
	while (arr[pos].key != "" && arr[pos].value != "")
	{
		pos = pos + i*i;
		pos %= maxSize;
		i++;
	}

	HashNode x(key, value);
	arr[pos] = x;
	++size;

	if (size*1.0f / maxSize >= 0.75)
	{
		size = 0;
		resize();
	}

}

string HashQuadratic::Lookup(string key)
{
	int pos = hash(key, maxSize);
	int i = 1;
	while (arr[pos].key != "" && arr[pos].value != "")
	{
		if (arr[pos].key == key)
			return arr[pos].value;
		pos = pos + i*i;
		pos %= maxSize;
		i++;
	}

	return "";
}

DoubleHash::DoubleHash(int M) : HashTable()
{
	arr = new HashNode[M]();
	size = 0;
	maxSize = M;
}

void DoubleHash::Insert(string key, string value)
{
	int pos = hash(key, maxSize);
	int pos2 = hash(key, 7) + 1;
	int i = 1;
	while (arr[pos].key != "" && arr[pos].value != "")
	{
		pos = pos + i*pos2;
		pos %= maxSize;
		i++;
	}

	HashNode x(key, value);
	arr[pos] = x;
	++size;

	if (size*1.0f / maxSize >= 0.75)
	{
		size = 0;
		resize();
	}

}

string DoubleHash::Lookup(string key)
{
	int pos = hash(key, maxSize);
	int pos2 = hash(key, 7) + 1;
	int i = 1;
	while (arr[pos].key != "" && arr[pos].value != "")
	{
		if (arr[pos].key == key)
			return arr[pos].value;
		pos = pos + i*pos2;
		pos %= maxSize;
		i++;
	}

	return "";
}