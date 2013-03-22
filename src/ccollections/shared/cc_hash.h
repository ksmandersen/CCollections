#ifndef CC_HASH_H
#define CC_HASH_H

#include <stdint.h>
#include <stdlib.h>

typedef uint64_t cc_hash;

typedef struct {
	void *data;
	size_t size;
} cc_hash_data;

cc_hash cc_hash_from_string(const char *str);
cc_hash cc_hash_from_data(const void *data, size_t size);

#endif
