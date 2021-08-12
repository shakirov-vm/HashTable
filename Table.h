
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
		potok << i << ": ";
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
}