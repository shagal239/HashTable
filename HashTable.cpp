//
//  HashTable.cpp
//  test
//
//  Created by Guest User on 25/05/15.
//  Copyright (c) 2015 Guest User. All rights reserved.
//

#include "HashTable.h"
	
unsigned long HashTable::HashFunction(const string &str)
{
	//Rs
	static const unsigned long b = 378551;
	unsigned long a = 63689;
	unsigned long hash = 0;

	for (unsigned int i = 0; i < str.length(); i++)
	{
		hash = hash * a + (unsigned char)str[i];
		a *= b;
	}

	return hash % size;
}

void HashTable::ClearList(HashList *list)
{
	if (list->next) ClearList(list->next);
	delete(list);
}

void HashTable::RemapList(HashList *list)
{
	if (list->next) RemapList(list->next);
	Add(list->key, list->value);
	delete(list);
}

void HashTable::ResizeArray(void)
{
	vector<HashList*> old_array = hash_array;
	hash_array = *new vector<HashList*>(size*=2);
	for (unsigned long i = 0; i < size; i++) hash_array[i] = NULL;
	for (unsigned long i = 0; i < size >> 1; i++)
	{
		if (old_array[i]) RemapList(old_array[i]);
	}
}

HashTable::HashTable()
{
	size = 256;
	hash_array = *new vector<HashList*>(size);
	for (unsigned long i = 0; i < size; i++) hash_array[i] = NULL;
}
	
HashTable::HashTable(const unsigned long size)
{
	this->size = size;
	hash_array = *new vector<HashList*>(size);
	for (unsigned long i = 0; i < size; i++) hash_array[i] = NULL;
}

HashTable::~HashTable()
{
	for (unsigned long i = 0; i < size; i++)
	{
		if (hash_array[i]) ClearList(hash_array[i]);
	}
}

bool HashTable::Add(const string &key, const string &value)
{
	HashList *new_value = new HashList();
	new_value -> key = key;
	new_value -> value = value;
	new_value -> next = NULL;
	HashList *last_value;
	if ((last_value = hash_array[HashFunction(key)]))
	{
		int count = 1;
		for (;;++count)
		{
			if (!last_value->key.compare(key))
			{
				delete(new_value);
				return false;
			}
			if (last_value->next) last_value = last_value->next;
			else break;
		}
		last_value->next = new_value;
		if (count > 4)
		{
			if (resizing) resize = true;
			else
			{
				do
				{
					resize = false;
					resizing = true;
					ResizeArray();
					resizing = false;
				} while (resize);
			}
		}
	}
	else hash_array[HashFunction(key)] = new_value;
	return true;
}

string* HashTable::Search(const string &key)
{
	HashList *current_value = hash_array[HashFunction(key)];
	if (current_value)
		for (;;)
		{
		   if (!current_value->key.compare(key)) return &current_value->value;
		   if (current_value->next) current_value = current_value->next;
		   else break;
		}
		return NULL;
}
	
bool HashTable::Delete(const string &key)
{
	HashList *current_value = hash_array[HashFunction(key)];
	HashList *last_value = current_value;
	if (current_value)
		for (;;)
		{
			if (!current_value->key.compare(key))
			{
				if (last_value == current_value) hash_array[HashFunction(key)] = current_value->next;
				else last_value = current_value->next;
				delete(current_value);
				return true;
			}
			if (current_value->next)
			{
				last_value = current_value;
				current_value = current_value->next;
			}
			else break;
		}
	return false;
}