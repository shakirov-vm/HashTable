
#define LIST_H
#ifdef LIST_H
#include "List.h"
#endif 

#define MINIMAL_TABLE 10

template <typename TYPE_H>
class HashTable {
public:
	List<TYPE_H>* table;
	size_t size;

	HashTable();
	void push(TYPE_H data_, size_t(*hash_func)(TYPE_H data_));
};

template <typename TYPE_H>
HashTable<TYPE_H>::HashTable() {
	size = MINIMAL_TABLE;
	table = new List<TYPE_H>[size]{};
}

template <typename TYPE_H>
void HashTable<TYPE_H>::push(TYPE_H data_, size_t(*hash_func)(TYPE_H data_)) {
	table[hash_func(data_) % size].push_back(data_);
}

