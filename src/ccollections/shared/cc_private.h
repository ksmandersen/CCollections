#ifndef CC_PRIVATE_H
#define CC_PRIVATE_H

#include "cc.h"
#include "cc_enumerator.h"

struct cc_collection_struct {
	bool (*enumerator_move_next)(struct cc_collection_struct *c, cc_enumerator *e);
};
typedef struct cc_collection_struct cc_collection;

#endif
