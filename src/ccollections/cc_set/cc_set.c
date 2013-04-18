#include "../shared/cc_private.h"
#include "cc_set.h"
#include "../shared/cc_enumerator_private.h"

const char * const cc_set_type = "cc_set_type";

#define HEAP_IMPLEMENTATION 1
#define LIST_IMPLEMENTATION 2

#define CURRENT_IMPLEMENTATION HEAP_IMPLEMENTATION

#if CURRENT_IMPLEMENTATION == HEAP_IMPLEMENTATION

static bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_set_compare(cc_object *obj1, cc_object *obj2);
static void cc_set_register_comparator();
static void cc_set_expand_heap(cc_set *set);

struct cc_set_struct {
	cc_collection c;
	cc_object **heap;
	int heap_size;
	int count;
};

cc_set *cc_set_new() {
	cc_set_register_comparator();
	
	cc_set *set;
	if ((set = GC_MALLOC(sizeof(cc_set))) == NULL) {
		return NULL;
	}
	
	set->c.enumerator_move_next = cc_set_enumerator_move_next;
	set->heap_size = 128;
	set->count = 0;
	set->heap = GC_MALLOC(sizeof(cc_object *) * set->heap_size);
	return set;
}

cc_enumerator *cc_set_get_enumerator(cc_set *set) {
	cc_enumerator *e = GC_MALLOC(sizeof(cc_enumerator));
	e->collection = (cc_collection *)set;
	e->data = GC_MALLOC(sizeof(int));
	*((int *)e->data) = -1;
	return e;
}

int cc_set_count(cc_set *set)
{
	return set->count;
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
	if (!cc_set_contains(set, obj)) {
		int i;
		for (i = 0; i < set->heap_size; i++) {
			if (i == set->heap_size) {
				cc_set_expand_heap(set);
			}
			if (set->heap[i] == NULL) {
				set->heap[i] = obj;
				set->count++;
				break;
			}
		}
	}
}

void cc_set_expand_heap(cc_set *set) {
	set->heap_size *= 2;
	set->heap = GC_REALLOC(set->heap, set->heap_size);
}

void cc_set_clear(cc_set *set) {
	int i;
	for (i = 0; i < set->count; i++) {
		set->heap[i] = NULL;
	}
	
	set->count = 0;
}

bool cc_set_contains(cc_set *set, cc_object *obj) {
	cc_enumerator *e = cc_set_get_enumerator(set);
	while (cc_enumerator_move_next(e)) {
		cc_object *obj2 = cc_enumerator_current(e);
		
		if (cc_object_is_equal(obj, obj2)) {
			return true;
		}
	}
	
	return false;
}

void cc_set_remove(cc_set *set, cc_object *obj) {
	int i;
	for (i = 0; i < set->count; i++) {
		if (cc_object_is_equal(obj, set->heap[i])) {
			set->heap[i] = NULL;
			set->count--;
		}
	}
}

cc_object *cc_set_to_object(cc_set *set) {
	return cc_object_with_data(set, sizeof(cc_set), cc_set_type);
}

cc_set *cc_set_from_object(cc_object *obj) {
	cc_set *set = cc_object_data_value(obj);
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

#elif CURRENT_IMPLEMENTATION == LIST_IMPLEMENTATION

#include "../cc_list/cc_list.h"

static bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e);
static bool cc_set_compare(cc_object *obj1, cc_object *obj2);
static void cc_set_register_comparator();

struct cc_set_struct {
	cc_collection c;
	cc_list *list;
};

cc_set *cc_set_new() {
	cc_set_register_comparator();
	cc_set *set = GC_MALLOC(sizeof(cc_set));
	set->c.enumerator_move_next = cc_set_enumerator_move_next;
	set->list = cc_list_new();
	return set;
}

cc_enumerator *cc_set_get_enumerator(cc_set *set) {
	return cc_list_get_enumerator(set->list);
}

bool cc_set_enumerator_move_next(cc_collection *c, cc_enumerator *e) {
	return cc_list_enumerator_move_next(c, e);
}

void cc_set_add(cc_set *set, cc_object *obj) {
	if (!cc_set_contains(set, obj)) {
		cc_list_add(set->list, obj);
	}
}

void cc_set_clear(cc_set *set) {
	cc_list_clear(set->list);
}

bool cc_set_contains(cc_set *set, cc_object *obj) {
	return cc_list_contains(set->list, obj);
}

void cc_set_remove(cc_set *set, cc_object *obj) {
	cc_list_remove(set->list, obj);
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
	return cc_list_compare(obj1->list, obj2->list);
}

void cc_set_register_comparator() {
	static bool first = true;
	
	if (first) {
		first = false;
		cc_object_register_comparator_for_type(cc_set_type, cc_set_compare);
	}
}

#endif
