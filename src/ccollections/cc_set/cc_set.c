#include "cc_private.h"
#include "cc_set.h"
#include "cc_enumerator_private.h"

const char * const cc_set_type = "cc_set_type";

bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e);
bool cc_set_compare(cc_object *obj1, cc_object *obj2);
void cc_set_register_comparator();

struct cc_set_struct {
	cc_collection c;
	cc_object **heap;
	int count;
};

cc_set *cc_set_new() {
	cc_set_register_comparator();
	cc_set *set = GC_MALLOC(sizeof(cc_set));
	set->c.enumerator_move_next = cc_set_enumerator_move_next;
	set->heap = GC_MALLOC(sizeof(cc_object *) * 128);
	return set;
}

cc_enumerator *cc_set_get_enumerator(cc_set *set) {
	cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
	e->collection = (cc_collection *)set;
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = -1;
	return e;
}

bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e) {
	int *counter = (int *)e->data;
	*counter = *counter + 1;
	cc_set *set = (cc_set *)c;
	
	if (*counter >= set->count) {
		return false;
	}
	
	e->current = set->heap[*counter];
	return true;
}

void cc_set_add(cc_set *set, cc_object *obj) {
	set->heap[set->count++] = obj;
}

void cc_set_clear(cc_set *set) {
	int i;
	for (i = 0; i < set->count; i++) {
		set->heap[i] = NULL;
	}
	
	set->count = 0;
}

bool cc_set_contains(cc_set *set, cc_object *obj) {
	return false;
}

void cc_set_remove(cc_set *set, cc_object *obj) {
	// nope
}

cc_object *cc_set_to_object(cc_set *set) {
	return cc_object_with_data(set, sizeof(cc_set), cc_set_type);
}

cc_set *cc_set_from_object(cc_object *obj) {
	cc_set *set = cc_set_new();
	cc_object_data_value(obj, (void **)&set, sizeof(cc_set));
	return set;
}

bool cc_set_compare(cc_object *obj1, cc_object *obj2) {
	cc_set *set1 = cc_set_from_object(obj1);
	cc_set *set2 = cc_set_from_object(obj2);
	
	cc_enumerator *e1 = cc_set_get_enumerator(set1);
	cc_enumerator *e2 = cc_set_get_enumerator(set2);
	while (cc_enumerator_move_next(e1)) {
		if (!cc_enumerator_move_next(e2)) return false;
		if (!cc_object_is_equal(cc_enumerator_current(e1), cc_enumerator_current(e2))) return false;
	}
	
	if (cc_enumerator_move_next(e2)) return false;
	return true;
}

void cc_set_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_set_type, cc_set_compare);
	}
}
