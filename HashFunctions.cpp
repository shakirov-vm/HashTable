
#include <string.h>
#include <stdio.h>

// Don't check data_ for nullptr

size_t hash_sum(char* data_) {
	size_t hash = 0;
	size_t len = strlen(data_);

	for (size_t i = 0; i < len; i++) hash += data_[i];
	//printf("Sum hash - %d - %s\n", hash, data_);
	return hash;
}

size_t hash_len(char* data_) {
	size_t hash = strlen(data_);
	return hash;
}

size_t hash_sbl(char* data_) {
	size_t hash = 0;
	size_t len = strlen(data_);

	for (size_t i = 0; i < len; i++) hash += data_[i];
	hash /= len;
	return hash;
}

size_t hash_ded(char* data_) {
	size_t hash = data_[0];
	return hash;
}

size_t hash_bit(char* data_) { // ??
	size_t hash = 0;
	size_t len = strlen(data_);

	for (size_t i = 0; i < len; i++) {
		hash <<= 1;
		hash ^= data_[i];
	}
	return hash;
}

size_t hash_pol(char* data_) {
	size_t hash = 0;
	size_t prime = 257;
	size_t len = strlen(data_);
	size_t degree = prime;

	for (size_t i = 0; i < len; i++) {
		hash += data_[i] * degree;
		degree *= prime;
	}
	return hash;
}