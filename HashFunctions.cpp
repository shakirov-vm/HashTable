
#include <string.h>

size_t hash_sum(char* data_) {
	size_t hash = 0;
	size_t len = strlen(data_);

	for (size_t i = 0; i < len; i++) hash += data_[i];
	return hash;
}