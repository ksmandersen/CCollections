#include "cc_hash.h"
#include <string.h>

cc_hash cc_hash_from_int(i) {
  return cc_hash_from_data(&i, sizeof(int));
}

cc_hash cc_hash_from_float(f) {
  return cc_hash_from_data(&f, sizeof(float));
}

cc_hash cc_hash_from_string(const char *str) {
	return cc_hash_from_data(str, strlen(str) + 1);
}

cc_hash cc_hash_from_data(const void *data, size_t size) {
	cc_hash sum = 0;
	
	size_t i;
	for (i = 0; i < size; i++) {
		sum += (((const char *)data)[i] * (i + 1 == 0? 1: i + 1));
	}
	
	return sum;
}
