#ifndef CC_PRIVATE_H
#define CC_PRIVATE_H

struct cc_collection_struct;
typedef struct cc_collection_struct cc_collection;

#include "cc.h"
#include "cc_enumerator_private.h"

struct cc_collection_struct {
	cc_enumerable enumerable;
};

#endif
