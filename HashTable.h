//
//  HashTable.h
//  test
//
//  Created by Guest User on 25/05/15.
//  Copyright (c) 2015 Guest User. All rights reserved.
//

#ifndef test_HashTable_h
#define test_HashTable_h
#include <string>
#include <vector>
using namespace std;

struct HashList
{
	string key, value;
	struct HashList *next;
};

class HashTable
{
private:
	unsigned long size;
	vector<HashList*> *hash_array;
	bool resizing, resize;
	
	unsigned long HashFunction(const string &str);
	void ClearList(HashList *list);
	void RemapList(HashList *list);
	void ResizeArray(void);
	
public:
	HashTable();
	HashTable(const unsigned long size);
	~HashTable();
	bool Add(const string &key, const string &value);
	string* Search(const string &key);
	bool Delete(const string &key);
};

#endif
