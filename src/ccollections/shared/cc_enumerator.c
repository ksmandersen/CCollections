#include "cc_private.h"
#include "cc_enumerator_private.h"

cc_object *cc_enumerator_current(cc_enumerator *e) {
	return e->current;
}

bool cc_enumerator_move_next(cc_enumerator *e) {
	return e->collection->enumerator_move_next(e->collection, e);
}
