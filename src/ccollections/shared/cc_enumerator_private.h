#ifndef CC_ENUMERATOR_PRIVATE_H
#define CC_ENUMERATOR_PRIVATE_H

#include "cc_enumerator.h"

struct cc_enumerable_struct;
typedef struct cc_enumerable_struct cc_enumerable;

typedef bool (*cc_enumerator_move_next_func)(cc_enumerable *c, cc_enumerator *e);

struct cc_enumerable_struct {
	cc_enumerator_move_next_func move_next;
};

struct cc_enumerator_struct {
	cc_enumerable *enumerable;
	void *data;
	cc_object *current;
};

cc_enumerator *cc_enumerator_new(cc_enumerable *e);

#endif
