#include "cc_private.h"
#include "cc_enumerator_private.h"
#include "cc_sorted_list.h"

typedef struct {
	cc_enumerator *parent;
	cc_enumerator_filter_func filter;
} filter_enumerator_data;

typedef struct {
	cc_enumerator *parent;
	cc_sorted_list *elements;
	cc_enumerator *elements_enumerator;
} order_enumerator_data;

static cc_enumerable *cc_enumerable_new(cc_enumerator_move_next_func move_next);
static bool cc_enumerator_filter_move_next(cc_enumerable *c, cc_enumerator *e);
static bool cc_enumerator_order_move_next(cc_enumerable *c, cc_enumerator *e);

cc_enumerator *cc_enumerator_new(cc_enumerable *e) {
	cc_enumerator *en = GC_MALLOC(sizeof(cc_enumerator));
	en->enumerable = e;
	en->current = NULL;
	return en;
}

cc_object *cc_enumerator_current(cc_enumerator *e) {
	return e->current;
}

bool cc_enumerator_move_next(cc_enumerator *e) {
	return e->enumerable->move_next(e->enumerable, e);
}

cc_enumerator *cc_enumerator_filter(cc_enumerator *e, cc_enumerator_filter_func filter) {
	cc_enumerator *en = cc_enumerator_new(cc_enumerable_new(cc_enumerator_filter_move_next));
	filter_enumerator_data *data = GC_malloc(sizeof(filter_enumerator_data));
	data->parent = e;
	data->filter = filter;
	en->data = data;
	return en;
}

cc_enumerator *cc_enumerator_order(cc_enumerator *e) {
	cc_enumerator *en = cc_enumerator_new(cc_enumerable_new(cc_enumerator_order_move_next));
	order_enumerator_data *data = GC_malloc(sizeof(order_enumerator_data));
	data->parent = e;
	data->elements = NULL;
	en->data = data;
	return en;
}

static cc_enumerable *cc_enumerable_new(cc_enumerator_move_next_func move_next) {
	cc_enumerable *e = GC_malloc(sizeof(cc_enumerator));
	e->move_next = move_next;
	return e;
}

bool cc_enumerator_filter_move_next(cc_enumerable *c, cc_enumerator *e) {
	filter_enumerator_data *data = e->data;
	cc_enumerator *parent_e = data->parent;
	
	while (cc_enumerator_move_next(parent_e)) {
		cc_object *obj = cc_enumerator_current(parent_e);
		
		if (data->filter(obj)) {
			e->current = obj;
			return true;
		}
	}
	
	return false;
}

static bool cc_enumerator_order_move_next(cc_enumerable *c, cc_enumerator *e) {
	order_enumerator_data *data = e->data;
	cc_enumerator *parent_e = data->parent;
	
	if (data->elements == NULL) {
		data->elements = cc_sorted_list_new();
		while (cc_enumerator_move_next(parent_e)) {
			cc_sorted_list_add(data->elements, cc_enumerator_current(parent_e));
		}
		data->elements_enumerator = cc_sorted_list_get_enumerator(data->elements);
	}
	
	bool status = cc_enumerator_move_next(data->elements_enumerator);
	e->current = cc_enumerator_current(data->elements_enumerator);
	return status;
}
