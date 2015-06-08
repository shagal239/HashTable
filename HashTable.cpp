//
//  HashTable.cpp
//  test
//
//  Created by Guest User on 25/05/15.
//  Copyright (c) 2015 Guest User. All rights reserved.
//

#include "HashTable.h"
#include <iostream>
#include <string>
using namespace std;

    unsigned long size;
    HashList **hash_array;
    
unsigned long HashTable::HashFunction(const string str)
{
       return str.length() % size;
}

void HashTable::ClearList(HashList *list)
{
    if (list->next) ClearList(list->next);
    else free(list);
}

HashTable::HashTable()
{
    size = 256;
    hash_array = new HashList*[size];
}
    
HashTable::HashTable(const unsigned long size)
{
    this->size = size;
    hash_array = new HashList*[size];
}

HashTable::~HashTable()
{
    for (unsigned long i = 0; i < size; i++)
    {
        if (hash_array[i]) ClearList(hash_array[i]);
    }
}

void HashTable::Add(const string key, const string value)
{
    HashList *new_value = new HashList();
    //new_value -> key.copy(key, key.length());
    new_value -> key = key; //!!!
    new_value -> value = value; //!!!
    new_value -> next = NULL;
    if(hash_array[HashFunction(key)])
    {
        hash_array[HashFunction(key)] = new_value;
        return;
    }
    HashList *last_value = hash_array[HashFunction(key)];
    if (last_value)
    {
        for (;;)
        {
            if (!last_value->key.compare(key))
            {
                //exceprion
                free(new_value);
                return;
            }
            if (last_value->next) last_value = last_value->next;
            else break;
        }
        last_value->next = new_value;
    }
    else
    {
        hash_array[HashFunction(key)] = new_value;
    }
}

string HashTable::Search(const string key)
{
    HashList *current_value = hash_array[HashFunction(key)];
    if (current_value)
        for (;;)
        {
           if (!current_value->key.compare(key)) return current_value->value;
           if (current_value->next) current_value = current_value->next;
           else break;
        }
        return string();
}
    
void HashTable::Delete(const string key)
{
    HashList *current_value = hash_array[HashFunction(key)];
    HashList *last_value = current_value;
    if (current_value)
        for (;;)
        {
            if (!current_value->key.compare(key))
            {
                if (last_value == current_value)
                {
                    hash_array[HashFunction(key)] = current_value->next;
                    free(current_value);
                }
                else
                {
                    last_value = current_value->next;
                    free(current_value);
                }
                return;
            }
            if (current_value->next)
            {
                last_value = current_value;
                current_value = current_value->next;
            }
            else break;
        }
    //exception
}