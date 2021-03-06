#include <iostream>
#include <stdlib.h>

template <typename TYPE>
class Node {
public:
	class Node<TYPE>* prev;
	TYPE* data;
	class Node<TYPE>* next;
public:
	Node();
	Node(class Node<TYPE>* prev_, class Node<TYPE>* next_, TYPE* data_);
};

template <typename TYPE>
Node<TYPE>::Node()
{
	printf("Unexpected\n");
	prev = nullptr;
	next = nullptr;
	data = nullptr;
}

template <typename TYPE>
Node<TYPE>::Node(class Node<TYPE>* prev_, class Node<TYPE>* next_, TYPE* data_)
{
	prev = prev_;
	next = next_;
	data = data_;
	printf(">> %p >> %p\n", this, this->data);
}
//===================================================================================================================================
template <typename TYPE>
class List {
	class Node<TYPE>* root;
	class Node<TYPE>* tail;

public:

	List() : root(nullptr), tail(nullptr) {};
	~List();
	List(TYPE* data_);
	void push_back(TYPE* data_);
	void push_front(TYPE* data_);
	TYPE* pop_back();
	TYPE* pop_front();
	void dump();
	bool is_empty();
};

template <typename TYPE>
List<TYPE>::List(TYPE* data_) {
	Node<TYPE>* node = new Node<TYPE>(nullptr, nullptr, data_);
	root = node;
	tail = node;
}

template <typename TYPE>
void List<TYPE>::push_back(TYPE* data_) {
	if (is_empty()) {
		printf("Empty\n");
		tail = new Node<TYPE>(nullptr, nullptr, data_);
		root = tail;
	}

	Node<TYPE>* node = new Node<TYPE>(tail, nullptr, data_);
	std::cout << *tail->data << " - " << tail->data << std::endl;
	tail->next = node;
	tail = node;
}

template <typename TYPE>
void List<TYPE>::push_front(TYPE* data_) {
	if (is_empty()) {
		root = new Node<TYPE>(nullptr, nullptr, data_);
		tail = root;
	}
	Node<TYPE>* node = new Node<TYPE>(nullptr, root, data_);
	root->prev = node;
	root = node;
}

template <typename TYPE>
TYPE* List<TYPE>::pop_back() {
	if (tail == nullptr) {
		printf("List is empty\n");
		return 0;
	}
	if (tail->prev == nullptr) {
		TYPE* tmp_ptr = tail->data;
		delete tail;
		tail = nullptr;
		root = nullptr;
		return tmp_ptr;
	}
	TYPE* tmp_ptr = tail->data;
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	return tmp_ptr;
}		

template <typename TYPE>
TYPE* List<TYPE>::pop_front() {
	if (root == nullptr) {
		printf("List is empty\n");
		return 0;
	}
	if (root->next == nullptr) {
		
		TYPE* tmp_ptr = root->data;
		
		delete root;
		root = nullptr;
		tail = nullptr;
		return tmp_ptr;
	}
	
	TYPE* tmp_ptr = root->data;
	root = root->next;

	delete root->prev;
	root->prev = nullptr;
	return tmp_ptr;
}

template <typename TYPE>
void List<TYPE>::dump() {
	if (is_empty()) return;
	Node<TYPE>* iterator = root;

	do {
		std::cout << "[" << *iterator->data << "] - " << iterator << " -> ";
		iterator = iterator->next;
	} while (iterator != nullptr);
	printf("\n\n\n");
}

template <typename TYPE> 
List<TYPE>::~List() {
	TYPE* tmp;
	Node<TYPE>* iterator = root;
	do {
		iterator = iterator->next;
		tmp = pop_front();
	} while (iterator != nullptr);
}

template <typename TYPE>
bool List<TYPE>::is_empty() {
	return (root == nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MINIMAL_TABLE 10

template<typename TYPE>
using hash_func = size_t(*)(TYPE*);

template <typename TYPE>
class HashTable {
public:
	List<TYPE>* table;
	size_t size;
	size_t capacity;
	hash_func<TYPE> count_hash;

	HashTable(hash_func<TYPE> hash);
	void push(TYPE* data_);
	void dump();
	void rehash();
};

template <typename TYPE>
HashTable<TYPE>::HashTable(hash_func<TYPE> hash) {
	count_hash = hash;
	capacity = MINIMAL_TABLE;
	size = 0;
	table = new List<TYPE>[capacity] {};
}

template <typename TYPE>
void HashTable<TYPE>::push(TYPE* data_) {
	if (size * 2 >= capacity) rehash();
	size_t index = (*count_hash)(data_) % capacity;
	if (table[index].is_empty()) size++;
	table[index].push_back(data_);
}

template <typename TYPE>
void HashTable<TYPE>::dump() {
	for (size_t i = 0; i < size; i++) table[i].dump();
}

template <typename TYPE>
void HashTable<TYPE>::rehash() {
	capacity *= 2;
	List<TYPE>* tmp_table = new List<TYPE>[capacity] {};

	TYPE* tmp_data; // no initile
	size_t index = 0;

	for (size_t i = 0; i < capacity / 2; i++) { // capacity divide by 2
		while (!(table[i].is_empty())) {
			tmp_data = table[i].pop_back();

			index = (*count_hash)(tmp_data) % capacity;
			if (table[index].is_empty()) size++;
			table[index].push_back(tmp_data);
		}
	}
	delete table;
	table = tmp_table;
}
