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
	Node& operator=(const Node& right);
	Node(class Node<TYPE>* prev_, class Node<TYPE>* next_, TYPE data_);
	~Node();
};

template <typename TYPE>
Node<TYPE>::Node()
{
	printf("Unexpected\n");
	prev = nullptr;
	next = nullptr;
	data = (TYPE*)calloc(1, sizeof(TYPE));
}

template <typename TYPE>
Node<TYPE>::Node(class Node<TYPE>* prev_, class Node<TYPE>* next_, TYPE data_)
{
	//printf("Create\n");
	prev = prev_;
	next = next_;
	data = new TYPE();//(TYPE*)calloc(1, sizeof(TYPE));
	if (data == nullptr) return;
	data[0] = data_;
	//std::cout << ">>> " << data[0] << std::endl;
}

template <typename TYPE>
Node<TYPE>& Node<TYPE>::operator=(const Node& right) {
	printf("Oi!\n");
}

template <typename TYPE>
Node<TYPE>::~Node() {
	printf("Try delete node %p\n", this);
	delete data;
	data = nullptr;
	//delete this;
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
	bool is_empty();
};

template <typename TYPE>
List<TYPE>::List(TYPE data_) {
	Node<TYPE>* node = new Node<TYPE>(nullptr, nullptr, data_);
	root = node;
	tail = node;
	//printf("NODE: [%p] - [%p] - [%p] - {%d}\n", node->prev, node, node->next, *(node->data));
}

template <typename TYPE>
void List<TYPE>::push_back(TYPE data_) {
	if (is_empty()) {
		tail = new Node<TYPE>(nullptr, nullptr, data_);
		root = tail;
		//printf("<%p> - <%p>\t", tail->prev, tail);
	}
	Node<TYPE>* node = new Node<TYPE>(tail, nullptr, data_);
	tail->next = node;
	tail = node;
	//printf("<%p> - <%p>\t", tail->prev, tail);
}

template <typename TYPE>
void List<TYPE>::push_front(TYPE data_) {
	if (is_empty()) {
		root = new Node<TYPE>(nullptr, nullptr, data_);
		tail = root;
	//	printf("<%p> - <%p>\t", root, root->next);
	}
	Node<TYPE>* node = new Node<TYPE>(nullptr, root, data_);
	root->prev = node;
	root = node;
	//printf("<%p> - <%p>\t", root, root->next);
}

template <typename TYPE>
TYPE List<TYPE>::pop_back() {
	if (tail == nullptr) {
		printf("List is empty\n");
		return 0;
	}
	if (tail->prev == nullptr) {
		//printf("{%p} \t", tail);
		TYPE tmp_ptr = *(tail->data);
		delete tail->data;
		delete tail;
		tail = nullptr;
		root = nullptr;
		return tmp_ptr;
	}
	//printf("{%p} \t", tail);
	TYPE tmp_ptr = *(tail->data);
	tail = tail->prev;
	delete tail->next->data;
	delete tail->next;
	tail->next = nullptr;
	return tmp_ptr;
}		//Сразу delete удалённого?

template <typename TYPE>
TYPE List<TYPE>::pop_front() {
	if (root == nullptr) {
		printf("List is empty\n");
		return 0;
	}
	if (root->next == nullptr) {
		//printf("{%p} \t", root);
		TYPE tmp_ptr = *(root->data);
		delete root->data;
		delete root;
		root = nullptr;
		tail = nullptr;
		return tmp_ptr;
	}
	//printf("{%p} \t", root);
	TYPE tmp_ptr = *(root->data);
	root = root->next;
	delete root->prev->data;
	delete root->prev;
	root->prev = nullptr;
	return tmp_ptr;
}

template <typename TYPE>
void List<TYPE>::dump() {
	if (is_empty()) return;
	//printf("root: [%p] - [%p] - [%p] - {%p}\n", root->prev, root, root->next, root->data);
	//printf("tail: [%p] - [%p] - [%p] - {%p}\n", tail->prev, tail, tail->next, tail->data); 
	Node<TYPE>* iterator = root;
	//printf("%p - %p - %d\n", root, iterator, *(iterator->data));
	do {
		std::cout << "[" << *(iterator->data) << "] -> ";
		iterator = iterator->next;
	} while (iterator != nullptr);
	printf("\n\n\n");
}

template <typename TYPE> 
List<TYPE>::~List() {
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

#define MINIMAL_TABLE 10

template <typename TYPE>
class HashTable {
public:
	List<TYPE>* table;
	size_t size;
	size_t capacity;

	HashTable();
	void push(TYPE data_, size_t(*hash_func)(TYPE data_));
	void dump();
	void rehash();
};

template <typename TYPE>
HashTable<TYPE>::HashTable() {
	capacity = MINIMAL_TABLE;
	size = 0;
	table = new List<TYPE>[capacity] {};
}

template <typename TYPE>
void HashTable<TYPE>::push(TYPE data_, size_t(*hash_func)(TYPE data_)) {
	if (size * 2 >= capacity) rehash();
	size_t index = hash_func(data_) % capacity;
	if (table[index].is_empty()) size++;
	table[index].push_back(data_);
}

template <typename TYPE>
void HashTable<TYPE>::dump() {
	for (size_t i = 0; i < size; i++) table[i].dump();
}

template <typename TYPE>
void HashTable<TYPE>::rehash() {
	List<TYPE>* tmp_table = new List<TYPE>[capacity * 2] {};

	for (size_t i = 0; i < capacity; i++) {
		while (!(table[i].is_empty())) {
			(table[i].pop_back()); // Hash fuction into class
		}
	}
}
