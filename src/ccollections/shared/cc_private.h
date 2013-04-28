#ifndef CC_PRIVATE_H
#define CC_PRIVATE_H

struct cc_collection_struct;
typedef struct cc_collection_struct cc_collection;

#include "cc.h"
#include "cc_enumerator_private.h"

struct cc_collection_struct {
	bool (*enumerator_move_next)(struct cc_collection_struct *c, cc_enumerator *e);
};

#endif
