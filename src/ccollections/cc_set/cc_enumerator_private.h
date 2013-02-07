#ifndef CC_ENUMERATOR_PRIVATE_H
#define CC_ENUMERATOR_PRIVATE_H

#include "cc_enumerator.h"

struct cc_enumerator_struct {
	cc_collection *collection;
	void *data;
	cc_object *current;
};

#endif
