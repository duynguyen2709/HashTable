#pragma once

#include <iostream>
#include <string>
using namespace std;


class HashTable;
class HashLinear;
class HashQuadratic;
class DoubleHash;


class HashNode
{
private:
	string value;
	string key;
	HashNode *next;
public:
	HashNode()
	{
		key = "";
		value = "";
	}

	HashNode(string _key, string _value)
	{
		value = _value;
		key = _key;
		next = NULL;
	}

	friend class HashTable;
	friend class HashLinear;
	friend class HashQuadratic;
	friend class DoubleHash;
};


class HashTable
{
private:
	HashNode **data;

protected:
	int maxSize;

	HashNode *arr = nullptr;
	HashNode *resize();

public:
	int size;
	HashTable(int M);
	~HashTable();
	HashTable() : data(nullptr), maxSize(0), size(0){}

	unsigned int hash(string key, int M);
	virtual void Insert(string key, string value);
	virtual string Lookup(string key);

};

class HashLinear :public HashTable
{
public:
	HashLinear(int M);
	virtual void Insert(string key, string value) override;
	virtual string Lookup(string key) override;
};

class HashQuadratic :public HashTable
{
public:
	HashQuadratic(int M);
	virtual void Insert(string key, string value) override;
	virtual string Lookup(string key) override;
};

class DoubleHash :public HashTable
{
public:
	DoubleHash(int M);
	virtual void Insert(string key, string value) override;
	virtual string Lookup(string key) override;
};