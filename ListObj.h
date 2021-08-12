#include <iostream>
#include <fstream>
#include <stdlib.h>

template <typename TYPE>
class Node {
public:
	class Node<TYPE>* prev;
	TYPE data;
	class Node<TYPE>* next;
public:
	Node();
	Node(class Node<TYPE>* prev_, class Node<TYPE>* next_, TYPE data_);
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
Node<TYPE>::Node(class Node<TYPE>* prev_, class Node<TYPE>* next_, TYPE data_)
{
	prev = prev_;
	next = next_;
	data = data_;
	//printf(">> %p >> %p\n", this, this->data);
}
//===================================================================================================================================
template <typename TYPE>
class List {
	class Node<TYPE>* root;
	class Node<TYPE>* tail;

public:

	List() : root(nullptr), tail(nullptr) {};
	~List();
	List(TYPE data_);
	void push_back(TYPE data_);
	void push_front(TYPE data_);
	TYPE pop_back();
	TYPE pop_front();
	void dump();
	void file_dump(std::ofstream& potok);
	bool is_empty();
	Node<TYPE>* find_node(TYPE data_);
	void delete_node(TYPE data_);
	size_t size();
};

template <typename TYPE>
List<TYPE>::List(TYPE data_) {
	Node<TYPE>* node = new Node<TYPE>(nullptr, nullptr, data_);
	root = node;
	tail = node;
}

template <typename TYPE>
void List<TYPE>::push_back(TYPE data_) {
	if (is_empty()) {
		//printf("Empty\n");
		tail = new Node<TYPE>(nullptr, nullptr, data_);
		root = tail;
		return;
	}

	Node<TYPE>* node = new Node<TYPE>(tail, nullptr, data_);
	//std::cout << tail->data << " " << std::endl;
	tail->next = node;
	tail = node;
}

template <typename TYPE>
void List<TYPE>::push_front(TYPE data_) {
	if (is_empty()) {
		root = new Node<TYPE>(nullptr, nullptr, data_);
		tail = root;
		return;
	}
	Node<TYPE>* node = new Node<TYPE>(nullptr, root, data_);
	root->prev = node;
	root = node;
}

template <typename TYPE>
TYPE List<TYPE>::pop_back() {
	if (tail == nullptr) {
		printf("List is empty\n");
		TYPE random;
		return random;
	}
	if (tail->prev == nullptr) {
		TYPE tmp_ptr = tail->data;
		delete tail;
		tail = nullptr;
		root = nullptr;
		return tmp_ptr;
	}
	TYPE tmp_ptr = tail->data;
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	return tmp_ptr;
}

template <typename TYPE>
TYPE List<TYPE>::pop_front() {
	if (root == nullptr) {
		printf("List is empty\n");
		TYPE random;
		return random;
	}
	if (root->next == nullptr) {

		TYPE tmp_ptr = root->data;

		delete root;
		root = nullptr;
		tail = nullptr;
		return tmp_ptr;
	}

	TYPE tmp_ptr = root->data;
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
		std::cout << "[" << iterator->data << "] -> "; // " << iterator << " -> ";
		iterator = iterator->next;
	} while (iterator != nullptr);
}


template <typename TYPE>
void List<TYPE>::file_dump(std::ofstream& potok) {
	if (is_empty()) return;
	Node<TYPE>* iterator = root;

	do {
		potok << "[" << iterator->data << "] -> "; // " << iterator << " -> ";
		iterator = iterator->next;
	} while (iterator != nullptr);
}

template <typename TYPE>
Node<TYPE>* List<TYPE>::find_node(TYPE data_) {
	if (is_empty()) {
		printf("List is empty, don't find\n");
		return nullptr;
	}
	Node<TYPE>* iterator = root;
	//std::cout << iterator->data << " - " << data_ << std::endl;
	//std::cout << iterator->data;
	while (iterator->data != data_) {
		if (iterator->next == nullptr) {
			printf("\nThis don't find\n");
			return nullptr;
		}
		iterator = iterator->next; 
		//std::cout << " -> " << iterator->data;
	}
	return iterator;
}

template <typename TYPE>
void List<TYPE>::delete_node(TYPE data_) {
	Node<TYPE>* iterator = find_node(data_);
	if (iterator == nullptr) {
		printf("\nThere no that node\n");
		return;
	}
	if (root == tail) {
		root = nullptr;
		tail = nullptr;
		return;
	}
	if (iterator == tail) tail = iterator->prev;
	if (iterator == root) root = iterator->next;
	if (iterator->prev != nullptr) iterator->prev->next = iterator->next;
	if (iterator->next != nullptr) iterator->next->prev = iterator->prev;
}


template <typename TYPE>
size_t List<TYPE>::size() {
	if (is_empty()) return 0;
	size_t size = 1;
	Node<TYPE>* iterator = root;
	while (iterator->next != nullptr) {
		iterator = iterator->next;
		++size;
	}
	return size;
}

template <typename TYPE>
List<TYPE>::~List() {
	if (is_empty()) return;
	TYPE tmp;
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
/*
#define MINIMAL_TABLE 10

template<typename KEY>
using hash_func = size_t(*)(KEY);

template<typename KEY, typename VALUE>
class pair {
public:
	KEY key;
	VALUE value;
	pair(KEY key_, VALUE value_) {
		key = key_;
		value = value_;
	}
	pair(KEY key_) {
		key = key_;
		value = 0;
	}
	pair() {
		key = 0;
		value = 0;
	}
	friend std::ostream& operator<< (std::ostream& out, const pair& pair_) {
		out << "[" << pair_.key << "] - [" << pair_.value << "]";
		return out;
	}
	bool operator== (const pair& right) { // you have both variations ?? No
		return (key == right.key);
	}
	bool operator!= (const pair& right) {
		return (key != right.key);
	}
};




template<typename KEY, typename VALUE>
class HashTable {

	List<pair<KEY, VALUE>>* table;
	size_t size;
	size_t capacity;
	hash_func<KEY> count_hash;

	void rehash();

public:
	HashTable(hash_func<KEY> hash);
	~HashTable();
	void push(KEY key, VALUE value);
	void dump();
	void file_dump();
	VALUE find_value(KEY key);
	void delete_value(KEY key);
	void list_size();
};

template<typename KEY, typename VALUE>
HashTable<KEY, VALUE>::HashTable(hash_func<KEY> hash) {
	count_hash = hash;
	capacity = MINIMAL_TABLE;
	size = 0;
	table = new List<pair<KEY, VALUE>>[capacity] {};
}

template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::push(KEY key, VALUE value) {
	if (size * 2 >= capacity) rehash();
	size_t index = (*count_hash)(key) % capacity;
	if (table[index].is_empty()) size++;
	class pair<KEY, VALUE> node(key, value); //Static?
	table[index].push_back(node);
}

template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::dump() {
	for (size_t i = 0; i < capacity; i++) {
		printf("%d: ", i);
		table[i].dump();
		printf("\n");
	}
}

template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::file_dump() {
	std::ofstream potok;
	potok.open("log.txt", std::ios::app);
	for (size_t i = 0; i < capacity; i++) {
		potok << i <<": ";
		table[i].file_dump(potok);
		potok << "\n";
	}
	potok << "\n";
	potok.close();
}

template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::rehash() {
	capacity *= 2;
	size = 0;
	List<pair<KEY, VALUE>>* tmp_table = new List<pair<KEY, VALUE>>[capacity] {};

	pair<KEY, VALUE> tmp_data; // no initile
	size_t index = 0;

	for (size_t i = 0; i < capacity / 2; i++) { // capacity divide by 2
		while (!(table[i].is_empty())) {
			tmp_data = table[i].pop_back();
			//std::cout << tmp_data;
			index = (*count_hash)(tmp_data.key) % capacity;
			if (tmp_table[index].is_empty()) size++;
			tmp_table[index].push_back(tmp_data);
		}
	}
	delete[] table;
	table = tmp_table;
}

template<typename KEY, typename VALUE>
HashTable<KEY, VALUE>::~HashTable() {
	delete[] table;
}

template<typename KEY, typename VALUE> 
VALUE HashTable<KEY, VALUE>::find_value(KEY key) {
	//std::cout << "\n\nkey - " << key << std::endl;
	class pair<KEY, VALUE> node(key);
	size_t index = (*count_hash)(key) % capacity;
	Node<pair<KEY, VALUE>>* iterator = table[index].find_node(node);
	if (iterator == nullptr) return 0;
	return iterator->data.value;
}

template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::delete_value(KEY key) {
	//std::cout << "\n\nkey - " << key << std::endl;
	class pair<KEY, VALUE> node(key);
	size_t index = (*count_hash)(key) % capacity;
	table[index].delete_node(node);
}

template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::list_size() {
	for (size_t i = 0; i < capacity; ++i) printf("%d: %d\n", i, table[i].size());
}*/